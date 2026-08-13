/**
 * @file    bsp_lightsensor.c
 * @brief   光敏传感器驱动实现
 *
 * 转换公式（经验标定）：
 *   光照强度 = 100 - K * V^N
 *   V = ADC 读数 * 3.3 / 4095
 */
#include "bsp_lightsensor.h"
#include "adc.h"
#include <math.h>

#define ADC_FULL_SCALE    4095U    /* 12 位 ADC 满量程 */
#define ADC_REF_VOLTAGE   3.3f     /* 参考电压 */
#define ADC_TIMEOUT_MS    100U     /* 转换超时 */

/* 电压→光照 标定参数 */
#define LIGHT_K   30.0f
#define LIGHT_N   1.5f

HAL_StatusTypeDef BSP_LightSensor_Init(ADC_HandleTypeDef *hadc)
{
    if (hadc == NULL) return HAL_ERROR;

    /* 启动 ADC 并保持运行，读取时只需 PollForConversion */
    return HAL_ADC_Start(hadc);
}

float BSP_LightSensor_Read(ADC_HandleTypeDef *hadc)
{
    float voltage;
    float lux;

    if (hadc == NULL) return -1.0f;

    if (HAL_ADC_PollForConversion(hadc, ADC_TIMEOUT_MS) != HAL_OK) {
        return -1.0f;   /* 读取失败返回错误值 */
    }

    voltage = (float)HAL_ADC_GetValue(hadc) * ADC_REF_VOLTAGE / (float)ADC_FULL_SCALE;

    lux = LIGHT_K * powf(voltage, LIGHT_N);

    /* 限幅 0~100 */
    if (lux > 100.0f) lux = 100.0f;
    if (lux < 0.0f)   lux = 0.0f;

    /* 返回 100-lux，与旧版显示逻辑保持一致（电压越高光照越弱） */
    return 100.0f - lux;
}
