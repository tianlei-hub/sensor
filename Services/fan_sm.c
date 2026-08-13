/**
 * @file    fan_sm.c
 * @brief   风扇状态机实现
 */
#include "fan_sm.h"

FanState_e FanSM_Process(FanState_e state, FanEvent_e evt)
{
    FanState_e next = state;

    switch (state) {
    case FAN_STATE_OFF:
        if (evt == FAN_EVT_SWITCH) {
            next = FAN_STATE_FULL;   /* 开机 → 全速 */
        } else if (evt == FAN_EVT_SPEED) {
            next = FAN_STATE_HALF;   /* 直接按SPEED → 半速启动 */
        }
        break;

    case FAN_STATE_HALF:
        if (evt == FAN_EVT_SWITCH) {
            next = FAN_STATE_OFF;    /* 关机 */
        } else if (evt == FAN_EVT_SPEED) {
            next = FAN_STATE_FULL;   /* 半速 → 全速 */
        }
        break;

    case FAN_STATE_FULL:
        if (evt == FAN_EVT_SWITCH) {
            next = FAN_STATE_OFF;    /* 关机 */
        } else if (evt == FAN_EVT_SPEED) {
            next = FAN_STATE_HALF;   /* 全速 → 半速 */
        }
        break;

    default:
        next = FAN_STATE_OFF;
        break;
    }

    return next;
}

uint8_t FanSM_GetDutyPercent(FanState_e state)
{
    switch (state) {
    case FAN_STATE_OFF:  return 0;
    case FAN_STATE_HALF: return 50;
    case FAN_STATE_FULL: return 100;
    default:             return 0;
    }
}
