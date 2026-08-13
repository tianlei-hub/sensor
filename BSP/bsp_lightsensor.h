/**
 * @file    bsp_lightsensor.h
 * @brief   光敏传感器驱动（ADC3_IN5, PF7）
 */
#ifndef __BSP_LIGHTSENSOR_H
#define __BSP_LIGHTSENSOR_H

#include "main.h"

/* 光照强度范围 0(暗) ~ 100(亮) */
#define LIGHT_MIN (0.0f)
#define LIGHT_MAX (100.0f)

/**
 * @brief 初始化光敏传感器（启动 ADC，之后持续运行）
 * @param hadc ADC 句柄（ADC3）
 * @retval HAL_OK / HAL_ERROR
 */
HAL_StatusTypeDef BSP_LightSensor_Init(ADC_HandleTypeDef *hadc);

/**
 * @brief 读取光照强度
 * @param hadc ADC 句柄
 * @retval 光照强度 0~100，读取失败返回 -1
 */
float BSP_LightSensor_Read(ADC_HandleTypeDef *hadc);

#endif /* __BSP_LIGHTSENSOR_H */
