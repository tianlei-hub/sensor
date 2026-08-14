/**
 * @file    task_cloud.c
 * @brief   云平台任务实现
 *
 * 状态机流程：
 *
 *   RESET ──▶ WIFI ──▶ TCP ──▶ TRANSPARENT ──▶ MQTT ──▶ ONLINE
 *      ▲          │                                        │
 *      └──────────┴────────── 任一步失败 ──────────────────┘
 *             （3s 退避，RST 复位模块重来）
 *
 * ONLINE 后：
 *   - 每 10s 读 DataModel 组 JSON 上报温湿度（PUBLISH QoS0，无 ACK）
 *   - 每 60s 发 PINGREQ 并等待 PINGRESP，超时判定断线
 */
#include "task_cloud.h"
#include "data_model.h"
#include "mqtt_client.h"
#include "bsp_mb026.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

#define CLOUD_BUF_SIZE          512U     /* MQTT 报文缓冲（CONNECT 约 165 字节） */
#define CLOUD_REPORT_PERIOD_MS  10000U   /* 属性上报周期 */
#define CLOUD_PING_PERIOD_MS    60000U   /* MQTT 心跳周期（与 KeepAlive 一致） */
/* 失败重连退避：不能太短——每次重连都要 RST 复位 WiFi 模块，
   ESP32 复位瞬间峰值电流大，频繁复位会拉跌开发板 USB 供电，
   导致 STM32/OLED 欠压异常（黑屏元凶） */
#define CLOUD_RETRY_DELAY_MS    15000U
#define CLOUD_WAIT_RESP_MS      8000U    /* 等 CONNACK/PINGRESP 超时 */

/* 云连接状态机 */
typedef enum {
    CLOUD_ST_RESET = 0,      /* 复位模块 + AT 初始化 */
    CLOUD_ST_WIFI,           /* 连路由器 + 设透传模式 */
    CLOUD_ST_TCP,            /* 连 OneNET 服务器 */
    CLOUD_ST_TRANSPARENT,    /* 进入透传 */
    CLOUD_ST_MQTT,           /* MQTT CONNECT 鉴权 */
    CLOUD_ST_ONLINE,         /* 在线：周期上报 + 心跳 */
} CloudFsmState_e;

/* 任务私有缓冲：仅本任务访问，用 static 省任务栈
 * （snprintf 的 %f 格式化栈开销约 1KB，局部大数组有栈溢出风险） */
static uint8_t s_mqtt_buf[CLOUD_BUF_SIZE];
static char    s_json_buf[192];

/**
 * @brief 从透传字节流读取一条完整 MQTT 报文
 * @param[out] pkt        完整报文（固定头 + 可变头 + 载荷）
 * @param[in]  cap        缓冲区容量
 * @param[in]  timeout_ms 读固定头第一字节的超时
 * @retval 报文总长（≥0），<0 接收失败
 * @note  固定头第一字节 → 变长剩余长度（1~4 字节逐字节读）
 *        → 按剩余长度读剩余部分
 */
static int32_t cloud_recv_packet(uint8_t *pkt, uint16_t cap, uint32_t timeout_ms)
{
    uint8_t  lenb[4];
    uint32_t rem  = 0;
    uint16_t pos  = 0;
    uint8_t  i, n;

    /* 固定头第一字节（含报文类型） */
    if (BSP_MB026_Recv(&pkt[pos], 1, timeout_ms) != 0) {
        return -1;
    }
    pos++;

    /* 剩余长度：逐字节读，直到 bit7=0 */
    for (i = 0; i < 4U; i++) {
        if (BSP_MB026_Recv(&lenb[i], 1, MB026_TO_RECV) != 0) {
            return -1;
        }
        pkt[pos++] = lenb[i];
        if ((lenb[i] & 0x80U) == 0U) {
            break;
        }
    }
    n = Mqtt_DecodeRemLen(lenb, (uint16_t)(i + 1U), &rem);
    if ((n == 0U) || (rem > (uint32_t)(cap - pos))) {
        return -2;                          /* 长度非法或缓冲不足 */
    }

    /* 剩余部分 */
    if (BSP_MB026_Recv(&pkt[pos], (uint16_t)rem, MB026_TO_RECV) != 0) {
        return -1;
    }
    pos += (uint16_t)rem;

    return (int32_t)pos;
}

/**
 * @brief 读 DataModel 并组 OneNET 属性上报 JSON
 * @param[out] out  输出缓冲区
 * @param[in]  size 缓冲区容量
 * @retval JSON 长度（不含 '\0'）
 */
static uint16_t cloud_build_report_json(char *out, uint16_t size)
{
    static uint16_t s_seq = 0;
    SensorData_t data;

    DataModel_Read(&data);
    return (uint16_t)snprintf(out, size,
        "{\"id\":\"%u\",\"version\":\"1.0\",\"params\":{"
        "\"CurrentTemperature\":{\"value\":%.1f},"
        "\"CurrentHumidity\":{\"value\":%.1f}}}",
        (unsigned)s_seq++, data.temperature, data.humidity);
}

/**
 * @brief 发送 PINGREQ 并等待 PINGRESP
 * @retval 0 收到心跳应答，<0 失败/超时
 */
static int32_t cloud_do_ping(void)
{
    uint16_t n = Mqtt_BuildPingreq(s_mqtt_buf);
    int32_t  r;

    if (BSP_MB026_Send(s_mqtt_buf, n) != 0) {
        return -1;
    }
    /* 循环读应答：丢弃非 PINGRESP 报文（如服务器主动推送） */
    do {
        r = cloud_recv_packet(s_mqtt_buf, sizeof(s_mqtt_buf), CLOUD_WAIT_RESP_MS);
        if (r < 0) {
            return -1;
        }
    } while (Mqtt_ParsePingresp(s_mqtt_buf, (uint16_t)r) != MQTT_OK);

    return 0;
}

void TaskCloud(void *argument)
{
    (void)argument;

    CloudFsmState_e fsm = CLOUD_ST_RESET;
    uint32_t last_report = 0;
    uint32_t last_ping   = 0;

    DataModel_WriteCloudState(CLOUD_OFFLINE);

    for (;;) {
        switch (fsm) {

        /* ---- 复位模块 + AT 初始化 ---- */
        case CLOUD_ST_RESET: {
            int32_t r;

            DataModel_WriteCloudState(CLOUD_CONNECTING);
            r = BSP_MB026_Init();
            if (r == 0) {
                fsm = CLOUD_ST_WIFI;
            } else {
                /* -2 = 串口完全无数据（接线/供电），其余 = 有数据但 AT 无应答 */
                DataModel_WriteCloudState((r == -2) ? CLOUD_INIT_FAIL : CLOUD_AT_FAIL);
                osDelay(CLOUD_RETRY_DELAY_MS);
            }
            break;
        }

        /* ---- 连路由器 + 设透传模式 ---- */
        case CLOUD_ST_WIFI:
            if ((BSP_MB026_JoinWifi() == 0) &&
                (BSP_MB026_SetTransparentMode() == 0)) {
                fsm = CLOUD_ST_TCP;
            } else {
                DataModel_WriteCloudState(CLOUD_WIFI_FAIL);
                osDelay(CLOUD_RETRY_DELAY_MS);
                fsm = CLOUD_ST_RESET;
            }
            break;

        /* ---- 连 OneNET 服务器 ---- */
        case CLOUD_ST_TCP:
            if (BSP_MB026_ConnectTcp(MQTT_HOST, MQTT_PORT) == 0) {
                fsm = CLOUD_ST_TRANSPARENT;
            } else {
                DataModel_WriteCloudState(CLOUD_TCP_FAIL);
                osDelay(CLOUD_RETRY_DELAY_MS);
                fsm = CLOUD_ST_RESET;
            }
            break;

        /* ---- 进入透传 ---- */
        case CLOUD_ST_TRANSPARENT:
            if (BSP_MB026_EnterTransparent() == 0) {
                fsm = CLOUD_ST_MQTT;
            } else {
                DataModel_WriteCloudState(CLOUD_TCP_FAIL);
                osDelay(CLOUD_RETRY_DELAY_MS);
                fsm = CLOUD_ST_RESET;
            }
            break;

        /* ---- MQTT CONNECT 鉴权 ---- */
        case CLOUD_ST_MQTT: {
            uint16_t n = Mqtt_BuildConnect(s_mqtt_buf, sizeof(s_mqtt_buf));
            int32_t  r;

            if ((n == 0U) || (BSP_MB026_Send(s_mqtt_buf, n) != 0)) {
                fsm = CLOUD_ST_RESET;
                break;
            }
            r = cloud_recv_packet(s_mqtt_buf, sizeof(s_mqtt_buf), CLOUD_WAIT_RESP_MS);
            if (r >= 0) {
                int32_t rc = Mqtt_ParseConnack(s_mqtt_buf, (uint16_t)r);

                if (rc == MQTT_OK) {
                    fsm = CLOUD_ST_ONLINE;
                    DataModel_WriteCloudState(CLOUD_ONLINE);
                    last_report = 0;        /* 上线后立即上报一次 */
                    last_ping   = HAL_GetTick();
                    break;
                }
                /* 服务器拒绝：记录返回码（1~5）或报文错误（254） */
                DataModel_WriteCloudDetail((rc > 0 && rc <= 5) ? (uint8_t)rc : 254U);
            } else {
                DataModel_WriteCloudDetail(255U);   /* 没收到 CONNACK */
            }
            DataModel_WriteCloudState(CLOUD_MQTT_FAIL);
            osDelay(CLOUD_RETRY_DELAY_MS);
            fsm = CLOUD_ST_RESET;
            break;
        }

        /* ---- 在线：周期上报 + 心跳 ---- */
        case CLOUD_ST_ONLINE: {
            uint32_t now = HAL_GetTick();

            /* 心跳保活（OneNET 30s~5min 收不到数据判定离线） */
            if ((now - last_ping) >= CLOUD_PING_PERIOD_MS) {
                if (cloud_do_ping() != 0) {
                    DataModel_WriteCloudState(CLOUD_OFFLINE);
                    osDelay(CLOUD_RETRY_DELAY_MS);
                    fsm = CLOUD_ST_RESET;
                    break;
                }
                last_ping = now;
            }

            /* 周期上报温湿度 */
            if ((now - last_report) >= CLOUD_REPORT_PERIOD_MS) {
                uint16_t n;

                (void)cloud_build_report_json(s_json_buf, sizeof(s_json_buf));
                n = Mqtt_BuildPublish(s_mqtt_buf, sizeof(s_mqtt_buf),
                                      MQTT_TOPIC_POST, s_json_buf);
                if ((n == 0U) || (BSP_MB026_Send(s_mqtt_buf, n) != 0)) {
                    fsm = CLOUD_ST_RESET;
                    break;
                }
                last_report = now;
            }

            osDelay(1000U);                 /* 1s 粒度轮询 */
            break;
        }

        default:
            fsm = CLOUD_ST_RESET;
            break;
        }
    }
}
