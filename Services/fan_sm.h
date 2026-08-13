/**
 * @file    fan_sm.h
 * @brief   风扇状态机
 *
 * 状态转移表：
 *
 *                 SWITCH按下
 *    ┌──────┐ ─────────────▶ ┌──────┐
 *    │ OFF  │                │ FULL │
 *    │PWM=0%│ ◀───────────── │PWM=100%
 *    └──────┘   SWITCH按下   └──────┘
 *       ▲                       │
 *       │ SPEED按下      SPEED按下│
 *       │         ┌───────┐      │
 *       └─────────│ HALF  │◀─────┘
 *                 │PWM=50%│
 *                 └───────┘
 */
#ifndef __FAN_SM_H
#define __FAN_SM_H

#include <stdint.h>

/* 风扇状态 */
typedef enum {
    FAN_STATE_OFF  = 0,
    FAN_STATE_HALF = 1,
    FAN_STATE_FULL = 2,
} FanState_e;

/* 按键事件 */
typedef enum {
    FAN_EVT_SWITCH = 0,  /* SWITCH键：开/关切换 */
    FAN_EVT_SPEED  = 1,  /* SPEED键：速度循环 */
} FanEvent_e;

/**
 * @brief 处理按键事件，执行状态转移
 * @param[in,out] state 当前状态，函数内更新为新状态
 * @param[in]     evt   按键事件
 * @retval 新状态
 */
FanState_e FanSM_Process(FanState_e state, FanEvent_e evt);

/**
 * @brief 获取状态对应的 PWM 占空比百分比 (0~100)
 * @param state 风扇状态
 * @retval 占空比 0 / 50 / 100
 */
uint8_t FanSM_GetDutyPercent(FanState_e state);

#endif /* __FAN_SM_H */
