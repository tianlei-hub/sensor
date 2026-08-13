/**
 * @file    app_entry.h
 * @brief   应用入口：服务初始化 + 任务创建
 */
#ifndef __APP_ENTRY_H
#define __APP_ENTRY_H

#include "cmsis_os2.h"
#include <stdint.h>

/* 按键事件类型 */
typedef enum {
    BTN_EVT_SWITCH = 0,   /* SWITCH键：风扇开/关 */
    BTN_EVT_SPEED  = 1,   /* SPEED键：风扇调速 */
    BTN_EVT_LIGHT  = 2,   /* LIGHT键：OLED亮/灭 */
} BtnEvent_e;

/* 按键事件队列（EXTI ISR → FanCtrlTask） */
extern osMessageQueueId_t g_btn_event_queue;

/* 任务句柄（任务间通知用） */
extern osThreadId_t g_sensor_task_handle;
extern osThreadId_t g_display_task_handle;
extern osThreadId_t g_fan_task_handle;

/**
 * @brief 应用入口
 * @note  由 MX_FREERTOS_Init() 调用，在调度器启动前完成所有初始化
 *        1. 服务层初始化（数据模型）
 *        2. BSP 驱动初始化（风扇/光敏/AHT20/OLED）
 *        3. 创建事件队列
 *        4. 创建 3 个应用任务
 */
void App_Entry(void);

/**
 * @brief 从 EXTI 中断回调发送按键事件（ISR 安全）
 * @param evt 按键事件
 * @note  调用于 HAL_GPIO_EXTI_Callback 中
 */
void App_NotifyBtnFromISR(BtnEvent_e evt);

#endif /* __APP_ENTRY_H */
