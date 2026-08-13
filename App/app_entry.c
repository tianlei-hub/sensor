/**
 * @file    app_entry.c
 * @brief   应用入口实现
 */
#include "app_entry.h"
#include "data_model.h"

#include "bsp_fan.h"
#include "bsp_lightsensor.h"
#include "bsp_aht20.h"

#include "oled.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"

/* ============ 任务原型（各任务文件实现） ============ */
void TaskSensor(void *argument);
void TaskDisplay(void *argument);
void TaskFan(void *argument);

/* ============ 全局句柄 ============ */
osMessageQueueId_t g_btn_event_queue = NULL;

/* 任务句柄（任务间通知用） */
osThreadId_t g_sensor_task_handle = NULL;
osThreadId_t g_display_task_handle = NULL;
osThreadId_t g_fan_task_handle = NULL;

/* 任务属性 */
static const osThreadAttr_t s_sensor_attr = {
    .name = "task_sensor",
    .stack_size = 512 * 4,
    .priority = osPriorityNormal,
};
static const osThreadAttr_t s_display_attr = {
    .name = "task_display",
    .stack_size = 1024 * 4,
    .priority = osPriorityLow,
};
static const osThreadAttr_t s_fan_attr = {
    .name = "task_fan",
    .stack_size = 512 * 4,
    .priority = osPriorityNormal,
};

void App_Entry(void)
{
    /* ---------- 1. 服务层 ---------- */
    DataModel_Init();

    /* ---------- 2. BSP 驱动初始化 ---------- */
    BSP_Fan_Init(&htim12);
    BSP_LightSensor_Init(&hadc3);
    BSP_AHT20_Init(&hi2c2);
    OLED_Init();

    /* ---------- 3. 事件队列 ---------- */
    g_btn_event_queue = osMessageQueueNew(8, sizeof(uint8_t), NULL);

    /* ---------- 4. 创建任务 ---------- */
    g_sensor_task_handle  = osThreadNew(TaskSensor,  NULL, &s_sensor_attr);
    g_display_task_handle = osThreadNew(TaskDisplay, NULL, &s_display_attr);
    g_fan_task_handle     = osThreadNew(TaskFan,     NULL, &s_fan_attr);
}

void App_NotifyBtnFromISR(BtnEvent_e evt)
{
    uint8_t payload = (uint8_t)evt;

    if (g_btn_event_queue != NULL) {
        /* CMSIS-RTOS v2 队列 API 可从 ISR 直接调用 */
        osMessageQueuePut(g_btn_event_queue, &payload, 0U, 0U);
    }
}
