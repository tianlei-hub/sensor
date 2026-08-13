/**
 * @file    data_model.h
 * @brief   全局传感器数据模型
 * @note    SensorTask 写入，DisplayTask 读取，互斥锁保护
 */
#ifndef __DATA_MODEL_H
#define __DATA_MODEL_H

#include "cmsis_os2.h"
#include "fan_sm.h"
#include <stdint.h>

/* 全局传感器数据 */
typedef struct {
    float  temperature;   /* 温度 ℃ */
    float  humidity;      /* 湿度 %RH */
    float  light;         /* 光照强度 0~100 */
    uint8_t fan_state;    /* 风扇状态 FanState_e */
    uint8_t display_on;   /* OLED 显示开关：1=亮 0=灭 */
    uint32_t update_cnt;  /* 数据更新计数（DisplayTask 可据此判断数据是否新鲜） */
} SensorData_t;

/* 由 data_model.c 定义 */
extern SensorData_t g_sensor_data;

/**
 * @brief 初始化数据模型（创建互斥锁）
 * @retval osOK 成功，其他值失败
 */
int32_t DataModel_Init(void);

/**
 * @brief 写入传感器数据（SensorTask 调用）
 * @param temp  温度
 * @param humid 湿度
 * @param lux   光照
 */
void DataModel_Write(float temp, float humid, float lux);

/**
 * @brief 读取传感器数据（DisplayTask 调用）
 * @param[out] out 数据副本
 */
void DataModel_Read(SensorData_t *out);

/**
 * @brief 写入风扇状态（FanCtrlTask 调用）
 * @param state 风扇状态
 */
void DataModel_WriteFanState(FanState_e state);

/**
 * @brief 翻转 OLED 显示开关（FanCtrlTask 处理 LIGHT 键时调用）
 */
void DataModel_ToggleDisplay(void);

#endif /* __DATA_MODEL_H */
