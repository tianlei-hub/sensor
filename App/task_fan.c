/**
 * @file    task_fan.c
 * @brief   风扇控制任务实现
 */
#include "task_fan.h"
#include "app_entry.h"
#include "data_model.h"
#include "fan_sm.h"
#include "bsp_fan.h"

/* 按键触发后的软件消抖延时（配合 ISR 的时间窗口消抖） */
#define FAN_DEBOUNCE_MS 50U

void TaskFan(void *argument)
{
    (void)argument;

    FanState_e state = FAN_STATE_OFF;
    uint8_t     payload;

    /* 初始状态：风扇关闭 */
    BSP_Fan_SetDuty(FanSM_GetDutyPercent(state));
    DataModel_WriteFanState(state);

    for (;;) {
        /* 阻塞等待按键事件 */
        if (osMessageQueueGet(g_btn_event_queue, &payload, NULL, osWaitForever) != osOK) {
            continue;
        }

        /* 软件消抖：延时后确认事件（硬件抖动在 ISR 层已做时间窗过滤） */
        osDelay(FAN_DEBOUNCE_MS);

        switch ((BtnEvent_e)payload) {
        case BTN_EVT_SWITCH:
            state = FanSM_Process(state, FAN_EVT_SWITCH);
            break;

        case BTN_EVT_SPEED:
            state = FanSM_Process(state, FAN_EVT_SPEED);
            break;

        case BTN_EVT_LIGHT:
            /* OLED 开关不涉及风扇状态机 */
            DataModel_ToggleDisplay();
            continue;

        default:
            continue;
        }

        /* 应用新状态：PWM 输出 + 数据模型同步 */
        BSP_Fan_SetDuty(FanSM_GetDutyPercent(state));
        DataModel_WriteFanState(state);
    }
}
