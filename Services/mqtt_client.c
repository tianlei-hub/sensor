/**
 * @file    mqtt_client.c
 * @brief   精简 MQTT 3.1.1 客户端实现
 */
#include "mqtt_client.h"
#include <string.h>

/* CONNECT 连接标志：CleanSession=1 | Password=1 | Username=1 */
#define CONNECT_FLAGS         0xC2U

/* CONNECT 可变头固定部分：协议名(2+4) + 协议级别(1) + 标志(1) + KeepAlive(2) = 10 */
#define CONNECT_VARHDR_LEN    10U

/* ============ 内部工具 ============ */

/**
 * @brief UTF-8 字符串编码：2 字节大端长度 + 内容
 * @retval 写入字节数（2 + len）
 */
static uint16_t enc_utf8(uint8_t *p, const char *s, uint16_t len)
{
    p[0] = (uint8_t)(len >> 8);
    p[1] = (uint8_t)(len & 0xFFU);
    if (len > 0U) {
        memcpy(&p[2], s, len);
    }
    return 2U + len;
}

/**
 * @brief 剩余长度变长编码（每字节低 7 位有效，最高位为继续标志）
 * @retval 编码字节数（1~4）
 */
static uint8_t enc_rem_len(uint8_t *p, uint32_t len)
{
    uint8_t n = 0;

    do {
        uint8_t byte = (uint8_t)(len % 128U);
        len /= 128U;
        if (len > 0U) {
            byte |= 0x80U;
        }
        p[n++] = byte;
    } while ((len > 0U) && (n < 4U));

    return n;
}

/* ============ 报文组包 ============ */

uint16_t Mqtt_BuildConnect(uint8_t *buf, uint16_t size)
{
    /* 协议名 "MQTT" + 协议级别 0x04 */
    static const uint8_t proto_hdr[] = {0x00, 0x04, 'M', 'Q', 'T', 'T', 0x04};

    uint16_t cid_len = (uint16_t)strlen(MQTT_CLIENT_ID);
    uint16_t usr_len = (uint16_t)strlen(MQTT_USERNAME);
    uint16_t pwd_len = (uint16_t)strlen(MQTT_PASSWORD);
    uint32_t rem_len = CONNECT_VARHDR_LEN
                     + 2U + cid_len
                     + 2U + usr_len
                     + 2U + pwd_len;
    uint16_t pos = 0;

    /* 固定头最多 5 字节（1 类型 + 4 长度），先做容量检查 */
    if (size < 5U + rem_len) {
        return 0;
    }

    buf[pos++] = 0x10U;                     /* CONNECT */
    pos += enc_rem_len(&buf[pos], rem_len);

    memcpy(&buf[pos], proto_hdr, sizeof(proto_hdr));
    pos += sizeof(proto_hdr);
    buf[pos++] = CONNECT_FLAGS;
    buf[pos++] = (uint8_t)(MQTT_KEEPALIVE_S >> 8);
    buf[pos++] = (uint8_t)(MQTT_KEEPALIVE_S & 0xFFU);

    /* 载荷：ClientID / Username / Password（顺序固定） */
    pos += enc_utf8(&buf[pos], MQTT_CLIENT_ID, cid_len);
    pos += enc_utf8(&buf[pos], MQTT_USERNAME, usr_len);
    pos += enc_utf8(&buf[pos], MQTT_PASSWORD, pwd_len);

    return pos;
}

uint16_t Mqtt_BuildPublish(uint8_t *buf, uint16_t size,
                           const char *topic, const char *payload)
{
    uint16_t topic_len = (uint16_t)strlen(topic);
    uint16_t pay_len   = (uint16_t)strlen(payload);
    uint32_t rem_len   = 2U + topic_len + pay_len;  /* QoS0：无报文标识符 */
    uint16_t pos = 0;

    if (size < 5U + rem_len) {
        return 0;
    }

    buf[pos++] = 0x30U;                     /* PUBLISH, QoS0 */
    pos += enc_rem_len(&buf[pos], rem_len);
    pos += enc_utf8(&buf[pos], topic, topic_len);
    memcpy(&buf[pos], payload, pay_len);
    pos += pay_len;

    return pos;
}

uint16_t Mqtt_BuildPingreq(uint8_t *buf)
{
    buf[0] = 0xC0U;
    buf[1] = 0x00U;
    return 2U;
}

/* ============ 报文解析 ============ */

int32_t Mqtt_ParseConnack(const uint8_t *buf, uint16_t len)
{
    if (len < 4U) {
        return MQTT_ERR_LEN;
    }
    if (buf[0] != MQTT_TYPE_CONNACK) {
        return MQTT_ERR_HDR;
    }
    if (buf[1] != 0x02U) {                  /* CONNACK 剩余长度恒为 2 */
        return MQTT_ERR_LEN;
    }
    /* buf[2]=确认标志（忽略），buf[3]=返回码：0 接受，1~5 拒绝 */
    return (int32_t)buf[3];
}

int32_t Mqtt_ParsePingresp(const uint8_t *buf, uint16_t len)
{
    if (len < 2U) {
        return MQTT_ERR_LEN;
    }
    if (buf[0] != MQTT_TYPE_PINGRESP) {
        return MQTT_ERR_HDR;
    }
    return MQTT_OK;
}

uint8_t Mqtt_DecodeRemLen(const uint8_t *p, uint16_t avail, uint32_t *rem_len)
{
    uint32_t value = 0U;
    uint32_t mul   = 1U;
    uint8_t  i;

    for (i = 0; i < 4U; i++) {
        if (avail <= i) {
            return 0;                       /* 数据不足 */
        }
        value += (uint32_t)(p[i] & 0x7FU) * mul;
        if ((p[i] & 0x80U) == 0U) {
            break;
        }
        mul *= 128U;
    }
    if (i == 4U) {
        return 0;                           /* 4 字节后仍未结束：编码非法 */
    }
    *rem_len = value;
    return (uint8_t)(i + 1U);
}
