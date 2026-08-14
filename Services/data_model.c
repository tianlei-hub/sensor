/**
 * @file    data_model.c
 * @brief   全局传感器数据模型实现
 */
#include "data_model.h"

/* 全局数据实例 */
SensorData_t g_sensor_data = {0};

/* 数据互斥锁 */
static osMutexId_t s_data_mutex = NULL;

int32_t DataModel_Init(void)
{
    s_data_mutex = osMutexNew(NULL);
    if (s_data_mutex == NULL) {
        return osError;
    }
    /* 默认 OLED 亮 */
    g_sensor_data.display_on = 1;
    return osOK;
}

void DataModel_Write(float temp, float humid, float lux)
{
    if (s_data_mutex == NULL) return;

    osMutexAcquire(s_data_mutex, osWaitForever);
    g_sensor_data.temperature = temp;
    g_sensor_data.humidity    = humid;
    g_sensor_data.light       = lux;
    g_sensor_data.update_cnt++;
    osMutexRelease(s_data_mutex);
}

void DataModel_Read(SensorData_t *out)
{
    if ((out == NULL) || (s_data_mutex == NULL)) return;

    osMutexAcquire(s_data_mutex, osWaitForever);
    *out = g_sensor_data;
    osMutexRelease(s_data_mutex);
}

void DataModel_WriteFanState(FanState_e state)
{
    if (s_data_mutex == NULL) return;

    osMutexAcquire(s_data_mutex, osWaitForever);
    g_sensor_data.fan_state = (uint8_t)state;
    osMutexRelease(s_data_mutex);
}

void DataModel_ToggleDisplay(void)
{
    if (s_data_mutex == NULL) return;

    osMutexAcquire(s_data_mutex, osWaitForever);
    g_sensor_data.display_on = (g_sensor_data.display_on == 0U) ? 1U : 0U;
    osMutexRelease(s_data_mutex);
}

void DataModel_WriteCloudState(CloudState_e state)
{
    if (s_data_mutex == NULL) return;

    osMutexAcquire(s_data_mutex, osWaitForever);
    g_sensor_data.cloud_state = (uint8_t)state;
    osMutexRelease(s_data_mutex);
}

void DataModel_WriteCloudDetail(uint8_t detail)
{
    if (s_data_mutex == NULL) return;

    osMutexAcquire(s_data_mutex, osWaitForever);
    g_sensor_data.cloud_detail = detail;
    osMutexRelease(s_data_mutex);
}
