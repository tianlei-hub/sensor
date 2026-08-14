/**
 * @file    mqtt_client.h
 * @brief   精简 MQTT 3.1.1 客户端（纯协议编解码，零硬件依赖）
 *
 * 仅实现 OneNET Studio 接入所需的最小报文集：
 *   发送: CONNECT / PUBLISH(QoS0) / PINGREQ
 *   接收: CONNACK / PINGRESP
 *
 * 设计要点：所有函数只操作缓冲区，不接触任何外设，
 * 实际收发由调用方（TaskCloud 经 BSP_MB026 透传）完成，
 * 因此本模块可在 PC 上独立单元测试。
 */
#ifndef __MQTT_CLIENT_H
#define __MQTT_CLIENT_H

#include <stdint.h>

/* ==================== OneNET Studio 接入参数 ==================== */
/* 产品级接入域名（OneNET 新格式：{产品ID}.mqtts.acc.cmcconenet.cn），
 * 旧域名 mqtts.heclouds.com 已导致鉴权失败（CONNACK 返回码 4） */
#define MQTT_HOST          "GRy0CBnliY.mqtts.acc.cmcconenet.cn"
#define MQTT_PORT          1883U
#define MQTT_CLIENT_ID     "test1"
#define MQTT_USERNAME      "GRy0CBnliY"
/* 用设备密钥（非产品 access_key）按官方算法生成的 token：
 * msg = et + '\n' + method + '\n' + res + '\n' + version
 * sign = base64(hmac_sha1(base64decode(device_key), msg))，sign 需 URL 编码 */
#define MQTT_PASSWORD      "version=2018-10-31&res=products%2FGRy0CBnliY%2Fdevices%2Ftest1&et=4102444800&method=sha1&sign=D0dn2drymDUft1O1HD6qwUZVpKc%3D"
/* 心跳周期（秒），OneNET 要求 30s~5min 之间 */
#define MQTT_KEEPALIVE_S   60U
/* 属性上报主题 */
#define MQTT_TOPIC_POST    "$sys/GRy0CBnliY/test1/thing/property/post"

/* 报文类型字节（固定头第一个字节） */
#define MQTT_TYPE_CONNACK   0x20U
#define MQTT_TYPE_PINGRESP  0xD0U

/* 解析返回值 */
#define MQTT_OK             0
#define MQTT_ERR_LEN       (-1)   /* 长度不足 / 剩余长度非法 */
#define MQTT_ERR_HDR       (-2)   /* 固定头类型不匹配 */

/**
 * @brief 组包 CONNECT（含 OneNET 鉴权：ClientID/Username/Password）
 * @param[out] buf  输出缓冲区
 * @param[in]  size 缓冲区容量
 * @retval 报文长度（字节），0 表示缓冲区不足
 */
uint16_t Mqtt_BuildConnect(uint8_t *buf, uint16_t size);

/**
 * @brief 组包 PUBLISH（QoS0，无报文标识符，无 ACK）
 * @param[out] buf     输出缓冲区
 * @param[in]  size    缓冲区容量
 * @param[in]  topic   主题名（UTF-8 字符串）
 * @param[in]  payload 消息内容（UTF-8 字符串）
 * @retval 报文长度（字节），0 表示缓冲区不足
 */
uint16_t Mqtt_BuildPublish(uint8_t *buf, uint16_t size,
                           const char *topic, const char *payload);

/**
 * @brief 组包 PINGREQ 心跳（定长 2 字节）
 * @param[out] buf 输出缓冲区（至少 2 字节）
 * @retval 报文长度（恒为 2）
 */
uint16_t Mqtt_BuildPingreq(uint8_t *buf);

/**
 * @brief 解析 CONNACK
 * @param[in] buf 完整报文（固定头+可变头）
 * @param[in] len 报文长度
 * @retval MQTT_OK     连接被接受
 * @retval 1~5         CONNACK 返回码（1=协议版本不支持 2=ClientID拒绝
 *                     3=服务器不可用 4=用户名/密码错误 5=未授权）
 * @retval MQTT_ERR_*  报文格式错误
 */
int32_t Mqtt_ParseConnack(const uint8_t *buf, uint16_t len);

/**
 * @brief 解析 PINGRESP
 * @param[in] buf 完整报文
 * @param[in] len 报文长度
 * @retval MQTT_OK 心跳应答正确，其余为错误
 */
int32_t Mqtt_ParsePingresp(const uint8_t *buf, uint16_t len);

/**
 * @brief 解码 MQTT 剩余长度字段（变长编码 1~4 字节）
 * @param[in]  p       指向剩余长度字段首字节
 * @param[in]  avail   p 起可用字节数
 * @param[out] rem_len 解码出的剩余长度
 * @retval 消耗的字节数（1~4），0 表示数据不足或编码非法
 */
uint8_t Mqtt_DecodeRemLen(const uint8_t *p, uint16_t avail, uint32_t *rem_len);

#endif /* __MQTT_CLIENT_H */
