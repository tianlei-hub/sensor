/**
 * @file    task_cloud.h
 * @brief   云平台任务：WiFi → TCP → MQTT → 周期上报 OneNET
 */
#ifndef __TASK_CLOUD_H
#define __TASK_CLOUD_H

#include "cmsis_os2.h"

/**
 * @brief 云任务入口（App_Entry 创建）
 * @param argument 未使用
 */
void TaskCloud(void *argument);

#endif /* __TASK_CLOUD_H */
