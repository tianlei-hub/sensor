/**
 * @file    bsp_fan.h
 * @brief   PWM 风扇驱动抽象
 * @note    硬件：TIM12_CH1 (PB14)，PWM 频率 20kHz
 */
#ifndef __BSP_FAN_H
#define __BSP_FAN_H

#include "main.h"

/* TIM12 PWM 参数 */
#define FAN_PWM_PERIOD      (4199U)  /* 自动重装载值 (84MHz/(4199+1) ≈ 20kHz) */
#define FAN_PWM_FULL_CMP    (4199U)  /* 100% 占空比 */
#define FAN_PWM_HALF_CMP    (2100U)  /* ~50% 占空比 */

/**
 * @brief 初始化风扇 PWM（占空比 0，不转动）
 * @param htim PWM 定时器句柄（TIM12）
 * @retval HAL_OK / HAL_ERROR
 */
HAL_StatusTypeDef BSP_Fan_Init(TIM_HandleTypeDef *htim);

/**
 * @brief 设置风扇占空比
 * @param percent 占空比百分比 0~100
 */
void BSP_Fan_SetDuty(uint8_t percent);

/**
 * @brief 读取当前占空比百分比
 * @retval 0~100
 */
uint8_t BSP_Fan_GetDuty(void);

#endif /* __BSP_FAN_H */
