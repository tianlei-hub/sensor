/**
 * @file    bsp_mb026.h
 * @brief   ATK-MB026 (ESP32-C3) WiFi 模块 AT 指令驱动
 * @note    硬件：USART3 (PB10 TX / PB11 RX) 115200 8N1，RST=PA4
 *
 * 职责：模块复位、AT 指令交互、连接路由器/云服务器、TCP 透传收发。
 * 用法：TaskCloud 通过本模块把 MQTT 报文字节流收发到 OneNET。
 *
 * 断线重连策略：任何环节失败一律 RST 复位重来，
 * 不使用 "+++" 退出透传（省去退出时序的复杂性）。
 */
#ifndef __BSP_MB026_H
#define __BSP_MB026_H

#include <stdint.h>

/* WiFi 接入点（路由器） */
#define MB026_WIFI_SSID    "Xiaomi 14"
#define MB026_WIFI_PASS    "12345678"

/* AT 应答超时 (ms) */
#define MB026_TO_AT        2000U     /* 常规 AT 命令 */
#define MB026_TO_WIFI      15000U    /* 连路由器（实际需 5~10s） */
#define MB026_TO_TCP       10000U    /* 连接云服务器 */
#define MB026_TO_RECV      5000U     /* 透传数据接收 */

/**
 * @brief 模块复位并初始化 AT 环境（RST→ATE0 关回显→STA 模式）
 * @retval 0 成功，<0 失败
 */
int32_t BSP_MB026_Init(void);

/**
 * @brief 连接 WiFi 路由器（SSID/密码取自上方的宏）
 * @retval 0 成功，<0 失败
 */
int32_t BSP_MB026_JoinWifi(void);

/**
 * @brief 设置 TCP 透传模式（AT+CIPMODE=1）
 * @retval 0 成功，<0 失败
 */
int32_t BSP_MB026_SetTransparentMode(void);

/**
 * @brief 连接 TCP 服务器（云平台）
 * @param host 域名（模块内部做 DNS 解析）
 * @param port 端口号
 * @retval 0 成功，<0 失败
 */
int32_t BSP_MB026_ConnectTcp(const char *host, uint16_t port);

/**
 * @brief 进入透传（清空残留数据 + AT+CIPSEND）
 * @note  此后模块不再解析 AT 指令，收发均为原始字节流
 * @retval 0 成功，<0 失败
 */
int32_t BSP_MB026_EnterTransparent(void);

/**
 * @brief 透传模式下发送字节流
 * @param data 数据指针
 * @param len  数据长度
 * @retval 0 成功，<0 失败
 */
int32_t BSP_MB026_Send(const uint8_t *data, uint16_t len);

/**
 * @brief 透传模式下阻塞接收指定长度字节流
 * @param[out] buf        接收缓冲区
 * @param[in]  len        期望接收长度
 * @param[in]  timeout_ms 超时时间
 * @retval 0 成功，<0 失败（超时/错误）
 */
int32_t BSP_MB026_Recv(uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/**
 * @brief 硬件复位模块（RST 低脉冲）
 * @note  断线重连的入口：任何状态失败后调用，回到干净初始状态
 */
void BSP_MB026_HardReset(void);

#endif /* __BSP_MB026_H */
