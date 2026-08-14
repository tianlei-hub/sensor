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

/* 云连接状态（TaskCloud 写入，DisplayTask 读取显示） */
typedef enum {
    CLOUD_OFFLINE    = 0,   /* 未连接 */
    CLOUD_CONNECTING = 1,   /* 连接中（WiFi/TCP/MQTT 任一环节） */
    CLOUD_ONLINE     = 2,   /* 已连上 OneNET */
    CLOUD_INIT_FAIL  = 3,   /* 模块 AT 初始化失败（串口完全无数据：接线/供电） */
    CLOUD_WIFI_FAIL  = 4,   /* 连 WiFi 失败（热点名/密码） */
    CLOUD_TCP_FAIL   = 5,   /* 连云服务器失败 */
    CLOUD_MQTT_FAIL  = 6,   /* MQTT CONNECT 鉴权失败 */
    CLOUD_AT_FAIL    = 7,   /* 串口有数据但 AT 无应答（模块时序/固件） */
} CloudState_e;

/* 全局传感器数据 */
typedef struct {
    float  temperature;   /* 温度 ℃ */
    float  humidity;      /* 湿度 %RH */
    float  light;         /* 光照强度 0~100 */
    uint8_t fan_state;    /* 风扇状态 FanState_e */
    uint8_t display_on;   /* OLED 显示开关：1=亮 0=灭 */
    uint8_t cloud_state;  /* 云连接状态 CloudState_e */
    uint8_t cloud_detail; /* 云失败详情：255=CONNACK 超时，1~5=CONNACK 返回码 */
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

/**
 * @brief 写入云连接状态（TaskCloud 调用）
 * @param state 云连接状态
 */
void DataModel_WriteCloudState(CloudState_e state);

/**
 * @brief 写入云失败详情（TaskCloud 调用，配合 CLOUD_MQTT_FAIL 使用）
 * @param detail 255=CONNACK 超时，1~5=CONNACK 返回码
 */
void DataModel_WriteCloudDetail(uint8_t detail);

#endif /* __DATA_MODEL_H */
