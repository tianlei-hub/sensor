/**
 * @file    bsp_fan.c
 * @brief   PWM 风扇驱动实现
 */
#include "bsp_fan.h"
#include "tim.h"

/* 当前使用的定时器句柄（初始化时记录） */
static TIM_HandleTypeDef *s_fan_tim = NULL;

HAL_StatusTypeDef BSP_Fan_Init(TIM_HandleTypeDef *htim)
{
    if (htim == NULL) return HAL_ERROR;

    s_fan_tim = htim;

    /* 先确保占空比为 0，再启动 PWM，防止上电瞬间风扇误转 */
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, 0);
    return HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
}

void BSP_Fan_SetDuty(uint8_t percent)
{
    uint32_t cmp;

    if (s_fan_tim == NULL) return;

    if (percent > 100) percent = 100;

    /* 占空比百分比 → 比较值 */
    cmp = (uint32_t)percent * FAN_PWM_FULL_CMP / 100U;

    __HAL_TIM_SET_COMPARE(s_fan_tim, TIM_CHANNEL_1, cmp);
}

uint8_t BSP_Fan_GetDuty(void)
{
    uint32_t cmp;

    if (s_fan_tim == NULL) return 0;

    cmp = __HAL_TIM_GET_COMPARE(s_fan_tim, TIM_CHANNEL_1);

    /* 比较值 → 占空比百分比 */
    return (uint8_t)(cmp * 100U / FAN_PWM_FULL_CMP);
}
