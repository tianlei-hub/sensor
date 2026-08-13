/**
 * @file    task_sensor.c
 * @brief   传感器采集任务实现
 */
#include "task_sensor.h"
#include "app_entry.h"
#include "data_model.h"
#include "data_filter.h"
#include "bsp_aht20.h"
#include "bsp_lightsensor.h"
#include "i2c.h"
#include "adc.h"

void TaskSensor(void *argument)
{
    (void)argument;

    AHT20_Data_t   aht = {0};
    float          light;
    FilterHandle_t f_temp;
    FilterHandle_t f_humid;
    FilterHandle_t f_light;
    float          temp_f  = 0.0f;
    float          humid_f = 0.0f;
    float          light_f = 0.0f;

    Filter_Init(&f_temp);
    Filter_Init(&f_humid);
    Filter_Init(&f_light);

    for (;;) {
        /* ---- AHT20 温湿度（失败则保留上一帧数据） ---- */
        if (BSP_AHT20_Read(&hi2c2, &aht) == HAL_OK) {
            temp_f  = Filter_Update(&f_temp,  aht.temperature);
            humid_f = Filter_Update(&f_humid, aht.humidity);
        }

        /* ---- 光敏传感器（失败则保留上一帧数据） ---- */
        light = BSP_LightSensor_Read(&hadc3);
        if (light >= 0.0f) {
            light_f = Filter_Update(&f_light, light);
        }

        /* ---- 发布到数据模型 ---- */
        DataModel_Write(temp_f, humid_f, light_f);

        /* ---- 通知显示任务刷新 ---- */
        if (g_display_task_handle != NULL) {
            osThreadFlagsSet(g_display_task_handle, DISPLAY_FLAG_REFRESH);
        }

        osDelay(SENSOR_PERIOD_MS);
    }
}
