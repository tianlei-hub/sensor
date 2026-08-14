/**
 * @file    bsp_mb026.c
 * @brief   ATK-MB026 AT 指令驱动实现
 */
#include "bsp_mb026.h"
#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

/* 复位后接收嗅探缓冲：用于区分"接线/供电问题"（无数据）与"模块异常"（有数据） */
static uint8_t  s_sniff_buf[64];
static uint16_t s_sniff_len = 0;

/* ============ 内部工具 ============ */

/**
 * @brief 发送 AT 命令并流式等待期望应答
 * @param cmd        命令文本（自动追加 \r\n）
 * @param expect     期望应答子串（NULL 表示只等命令完成）
 * @param timeout_ms 总超时
 * @retval 0 成功，-1 收到 ERROR，-2 超时且完全无数据，-3 超时但收到过数据
 * @note  逐字节接收累积到小缓冲后 strstr 匹配，
 *        对 AT 固件的异步打印（WIFI GOT IP 等）不敏感
 */
static int32_t mb026_at_cmd(const char *cmd, const char *expect,
                            uint32_t timeout_ms)
{
    char     rsp[64] = {0};
    uint16_t idx     = 0;
    uint8_t  got_data = 0;
    uint32_t start   = HAL_GetTick();

    HAL_UART_Transmit(&huart3, (uint8_t *)cmd, (uint16_t)strlen(cmd), 1000U);
    HAL_UART_Transmit(&huart3, (uint8_t *)"\r\n", 2, 1000U);

    while ((HAL_GetTick() - start) < timeout_ms) {
        uint8_t ch;
        if (HAL_UART_Receive(&huart3, &ch, 1, 100) != HAL_OK) {
            continue;                       /* 100ms 无数据，继续等 */
        }
        got_data = 1;
        if (idx < sizeof(rsp) - 1U) {
            rsp[idx++] = (char)ch;
        }
        if ((expect != NULL) && (strstr(rsp, expect) != NULL)) {
            return 0;
        }
        if (strstr(rsp, "ERROR") != NULL) {
            return -1;
        }
    }
    return got_data ? -3 : -2;              /* 超时：区分有无数据 */
}

/**
 * @brief 清空接收缓冲中的残留数据
 * @note  进入透传前必须调用：路由器连接成功等异步打印
 *        会残留在串口流里，不清理会污染 MQTT 报文解析
 */
static void mb026_drain_rx(void)
{
    uint8_t  ch;
    uint16_t idle = 0;

    while (idle < 5U) {                     /* 连续 500ms 无数据视为清空 */
        if (HAL_UART_Receive(&huart3, &ch, 1, 100) == HAL_OK) {
            idle = 0;
        } else {
            idle++;
        }
    }
}

/* ============ 对外接口 ============ */

void BSP_MB026_HardReset(void)
{
    uint8_t  ch;
    uint32_t start;

    s_sniff_len = 0;                        /* 重置嗅探缓冲 */

    /* RST 拉低至少 100ms 复位模块（低电平有效） */
    HAL_GPIO_WritePin(WIFI_RST_GPIO_Port, WIFI_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(WIFI_RST_GPIO_Port, WIFI_RST_Pin, GPIO_PIN_SET);

    /* 等模块启动（ESP32 冷启动到 AT ready 约 1~2s），边等边收：
     * 若 RST 生效，模块 boot 日志会在此窗口流出。
     * 收不到任何字节 = 接线/供电问题（返回 -2 供上层区分显示） */
    start = HAL_GetTick();
    while ((HAL_GetTick() - start) < 3000U) {
        if (HAL_UART_Receive(&huart3, &ch, 1, 50) == HAL_OK) {
            if (s_sniff_len < sizeof(s_sniff_buf)) {
                s_sniff_buf[s_sniff_len++] = ch;
            }
        }
    }
}

int32_t BSP_MB026_Init(void)
{
    int32_t r;

    BSP_MB026_HardReset();                  /* 内含 3s 启动等待 + 边等边收 */

    if (s_sniff_len == 0) {
        return -2;                          /* 复位后 3s 完全无数据：接线/供电问题 */
    }

    /* AT 启动测试：对齐官方驱动（"AT"→"OK"，重试 10 次 × 500ms） */
    r = -1;
    for (uint8_t i = 0; i < 10U; i++) {
        r = mb026_at_cmd("AT", "OK", 500);
        if (r == 0) {
            break;
        }
    }
    if (r != 0) {
        return -3;                          /* 有数据但 AT 无应答：模块状态异常 */
    }
    /* 关回显：避免 AT 命令回显污染应答流 */
    if (mb026_at_cmd("ATE0", "OK", MB026_TO_AT) != 0) {
        return -4;
    }
    /* WiFi 模式 = Station（连接路由器） */
    if (mb026_at_cmd("AT+CWMODE=1", "OK", MB026_TO_AT) != 0) {
        return -4;
    }
    return 0;
}

int32_t BSP_MB026_JoinWifi(void)
{
    char    cmd[64];
    int32_t r;

    snprintf(cmd, sizeof(cmd),
             "AT+CWJAP=\"%s\",\"%s\"", MB026_WIFI_SSID, MB026_WIFI_PASS);
    /* 手机热点连接偶发超时（信号/热点响应慢），失败后隔 2s 重试一次 */
    r = mb026_at_cmd(cmd, "OK", MB026_TO_WIFI);
    if (r != 0) {
        HAL_Delay(2000);
        r = mb026_at_cmd(cmd, "OK", MB026_TO_WIFI);
    }
    return r;
}

int32_t BSP_MB026_SetTransparentMode(void)
{
    return mb026_at_cmd("AT+CIPMODE=1", "OK", MB026_TO_AT);
}

int32_t BSP_MB026_ConnectTcp(const char *host, uint16_t port)
{
    char cmd[80];

    snprintf(cmd, sizeof(cmd),
             "AT+CIPSTART=\"TCP\",\"%s\",%u", host, (unsigned)port);
    return mb026_at_cmd(cmd, "OK", MB026_TO_TCP);
}

int32_t BSP_MB026_EnterTransparent(void)
{
    /* 清空残留（WIFI GOT IP 等异步打印），保证透传首字节即 MQTT 报文 */
    mb026_drain_rx();

    /* CIPSEND 应答 ">" 后进入透传 */
    if (mb026_at_cmd("AT+CIPSEND", ">", MB026_TO_AT) != 0) {
        return -1;
    }
    return 0;
}

int32_t BSP_MB026_Send(const uint8_t *data, uint16_t len)
{
    if (HAL_UART_Transmit(&huart3, (uint8_t *)data, len, 2000U) != HAL_OK) {
        return -1;
    }
    return 0;
}

int32_t BSP_MB026_Recv(uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
    if (HAL_UART_Receive(&huart3, buf, len, timeout_ms) != HAL_OK) {
        return -1;
    }
    return 0;
}
