/**
 * @file    bsp_aht20.h
 * @brief   AHT20 温湿度传感器驱动
 * @note    硬件：I2C2 (PF0 SDA / PF1 SCL)，地址 0x38
 *
 * 测量时序（参考 AHT20 数据手册）：
 *   1. 发送测量命令 0xAC 0x33 0x00
 *   2. 等待状态寄存器 bit7 = 0（测量完成，典型 75ms）
 *   3. 读取 6 字节数据并计算温湿度
 */
#ifndef __BSP_AHT20_H
#define __BSP_AHT20_H

#include "main.h"

#define AHT20_ADDR          (0x38U << 1)  /* 7位地址0x38，左移1位 */
#define AHT20_I2C_TIMEOUT   100U          /* I2C 超时 ms */
#define AHT20_MEASURE_WAIT  80U           /* 测量等待 ms */

/**
 * @brief AHT20 测量结果
 */
typedef struct {
    float temperature;   /* 温度 ℃ */
    float humidity;      /* 湿度 %RH */
} AHT20_Data_t;

/**
 * @brief 初始化 AHT20（上电等待 + 校准命令）
 * @param hi2c I2C 句柄（I2C2）
 * @retval HAL_OK / HAL_ERROR / HAL_TIMEOUT
 */
HAL_StatusTypeDef BSP_AHT20_Init(I2C_HandleTypeDef *hi2c);

/**
 * @brief 触发一次测量并读取结果
 * @param hi2c  I2C 句柄
 * @param[out] data 测量结果
 * @retval HAL_OK 成功；其他值失败（data 内容无效）
 */
HAL_StatusTypeDef BSP_AHT20_Read(I2C_HandleTypeDef *hi2c, AHT20_Data_t *data);

#endif /* __BSP_AHT20_H */
