/**
 * @file    bsp_aht20.c
 * @brief   AHT20 温湿度传感器驱动实现
 *
 * 修复原 AHT20.C 的问题：
 *   - I2C 句柄参数化（依赖注入，不再硬编码 hi2c2）
 *   - 所有 I2C 调用检查返回值
 *   - 温湿度计算仅在读取成功后执行（避免脏数据）
 *   - 用状态位轮询替代固定 HAL_Delay
 */
#include "bsp_aht20.h"

/* AHT20 命令 */
#define AHT20_CMD_CALIBRATE  0xBEU  /* 校准命令 */
#define AHT20_CMD_STATUS     0x71U  /* 读状态命令 */
#define AHT20_CMD_MEASURE    0xACU  /* 触发测量 */

/* 测量数据转换常量（AHT20 数据手册） */
#define AHT20_DIV_2M      1048576.0f  /* 2^20 */
#define AHT20_TEMP_OFFSET 50.0f
#define AHT20_TEMP_GAIN   200.0f

HAL_StatusTypeDef BSP_AHT20_Init(I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef ret;
    uint8_t status = 0;

    if (hi2c == NULL) return HAL_ERROR;

    /* 上电后等待传感器稳定（数据手册要求 >40ms） */
    HAL_Delay(AHT20_MEASURE_WAIT / 2);

    /* 读状态寄存器，检查是否已校准 */
    ret = HAL_I2C_Master_Transmit(hi2c, AHT20_ADDR, &(uint8_t){AHT20_CMD_STATUS},
                                  1, AHT20_I2C_TIMEOUT);
    if (ret != HAL_OK) return ret;

    ret = HAL_I2C_Master_Receive(hi2c, AHT20_ADDR, &status, 1, AHT20_I2C_TIMEOUT);
    if (ret != HAL_OK) return ret;

    /* bit3 = 0 表示未校准，发送校准命令 */
    if ((status & 0x08U) == 0U) {
        ret = HAL_I2C_Master_Transmit(hi2c, AHT20_ADDR, &(uint8_t){AHT20_CMD_CALIBRATE},
                                      1, AHT20_I2C_TIMEOUT);
        if (ret != HAL_OK) return ret;
        HAL_Delay(10);
    }

    return HAL_OK;
}

HAL_StatusTypeDef BSP_AHT20_Read(I2C_HandleTypeDef *hi2c, AHT20_Data_t *data)
{
    HAL_StatusTypeDef ret;
    uint8_t cmd[3] = {AHT20_CMD_MEASURE, 0x33, 0x00};
    uint8_t buf[6] = {0};
    uint8_t status;
    uint32_t tmp_raw;
    uint32_t hum_raw;
    uint8_t  tries;

    if ((hi2c == NULL) || (data == NULL)) return HAL_ERROR;

    /* 1. 触发测量 */
    ret = HAL_I2C_Master_Transmit(hi2c, AHT20_ADDR, cmd, 3, AHT20_I2C_TIMEOUT);
    if (ret != HAL_OK) return ret;

    /* 2. 轮询状态位，等待测量完成（bit7=0 表示完成） */
    for (tries = 0; tries < 20; tries++) {
        HAL_Delay(10);
        ret = HAL_I2C_Master_Receive(hi2c, AHT20_ADDR, &status, 1, AHT20_I2C_TIMEOUT);
        if (ret != HAL_OK) return ret;
        if ((status & 0x80U) == 0U) break;   /* 测量完成 */
    }
    if (tries >= 20) return HAL_TIMEOUT;     /* 200ms 仍未完成 */

    /* 3. 读取 6 字节数据 */
    ret = HAL_I2C_Master_Receive(hi2c, AHT20_ADDR, buf, 6, AHT20_I2C_TIMEOUT);
    if (ret != HAL_OK) return ret;

    /* 4. 计算温湿度（仅在读取成功后） */
    tmp_raw = ((uint32_t)(buf[3] & 0x0FU) << 16) | ((uint32_t)buf[4] << 8) | buf[5];
    hum_raw = ((uint32_t)buf[1] << 12) | ((uint32_t)buf[2] << 4) | ((buf[3] & 0xF0U) >> 4);

    data->temperature = (float)tmp_raw / AHT20_DIV_2M * AHT20_TEMP_GAIN - AHT20_TEMP_OFFSET;
    data->humidity    = (float)hum_raw / AHT20_DIV_2M * 100.0f;

    return HAL_OK;
}
