/**
 * @file    task_display.c
 * @brief   OLED 显示任务实现
 */
#include "task_display.h"
#include "task_sensor.h"
#include "data_model.h"

#include "oled.h"
#include <stdio.h>

/* 风扇动画帧号（2 帧循环） */
static uint8_t s_fan_frame = 0;

void TaskDisplay(void *argument)
{
    (void)argument;

    SensorData_t data;
    uint8_t      last_display_on = 1;
    char         str_temp[20]  = {0};
    char         str_humid[20] = {0};
    char         str_light[20] = {0};
    char         str_cloud[12] = {0};

    for (;;) {
        /* 等待传感器任务刷新通知 */
        osThreadFlagsWait(DISPLAY_FLAG_REFRESH, osFlagsWaitAny, osWaitForever);

        DataModel_Read(&data);

        /* ---- LIGHT 键切换显示开关 ---- */
        if (data.display_on != last_display_on) {
            last_display_on = data.display_on;
            if (data.display_on) {
                OLED_DisPlay_On();
            } else {
                OLED_DisPlay_Off();
            }
        }

        /* 显示关闭时跳过绘制（屏幕物理上已关闭） */
        if (data.display_on == 0U) {
            continue;
        }

        /* ---- 格式化数据 ---- */
        snprintf(str_temp,  sizeof(str_temp),  "温度:%0.1f℃", data.temperature);
        snprintf(str_humid, sizeof(str_humid), "湿度:%0.1f%%", data.humidity);
        snprintf(str_light, sizeof(str_light), "光照:%0.1f",  data.light);
        switch (data.cloud_state) {
            case CLOUD_ONLINE:
                snprintf(str_cloud, sizeof(str_cloud), "CLD:ON");
                break;
            case CLOUD_CONNECTING:
                snprintf(str_cloud, sizeof(str_cloud), "CLD:..");
                break;
            case CLOUD_INIT_FAIL:
                snprintf(str_cloud, sizeof(str_cloud), "CLD:INIT");
                break;
            case CLOUD_WIFI_FAIL:
                snprintf(str_cloud, sizeof(str_cloud), "CLD:WIFI");
                break;
            case CLOUD_TCP_FAIL:
                snprintf(str_cloud, sizeof(str_cloud), "CLD:TCP");
                break;
            case CLOUD_MQTT_FAIL:
                if (data.cloud_detail == 255U) {
                    snprintf(str_cloud, sizeof(str_cloud), "CLD:MTMO");
                } else if ((data.cloud_detail >= 1U) && (data.cloud_detail <= 5U)) {
                    snprintf(str_cloud, sizeof(str_cloud), "CLD:MT%u",
                             (unsigned)data.cloud_detail);
                } else {
                    snprintf(str_cloud, sizeof(str_cloud), "CLD:MQTT");
                }
                break;
            case CLOUD_AT_FAIL:
                snprintf(str_cloud, sizeof(str_cloud), "CLD:AT");
                break;
            default:
                snprintf(str_cloud, sizeof(str_cloud), "CLD:OFF");
                break;
        }

        /* ---- 绘制帧 ---- */
        OLED_NewFrame();

        /* 风扇图标动画：运行中 2 帧交替，停止时显示静止帧 */
        if (data.fan_state != FAN_STATE_OFF) {
            if (s_fan_frame == 0) {
                OLED_DrawImage(70, 2, &fan0Img, OLED_COLOR_NORMAL);
            } else {
                OLED_DrawImage(70, 2, &fan1Img, OLED_COLOR_NORMAL);
            }
            s_fan_frame ^= 1U;   /* 0↔1 交替 */
        } else {
            OLED_DrawImage(70, 2, &fan0Img, OLED_COLOR_NORMAL);
            s_fan_frame = 0;
        }

        OLED_PrintString(2, 38, str_light, &font12x12, OLED_COLOR_NORMAL);
        OLED_PrintString(2, 2,  str_temp,  &font12x12, OLED_COLOR_NORMAL);
        OLED_PrintString(2, 20, str_humid, &font12x12, OLED_COLOR_NORMAL);
        OLED_PrintString(2, 52, str_cloud, &font12x12, OLED_COLOR_NORMAL);
        OLED_ShowFrame();
    }
}
