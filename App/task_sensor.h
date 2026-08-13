/**
 * @file    task_sensor.h
 * @brief   传感器采集任务
 *
 * 周期 500ms：
 *   AHT20 温湿度 + 光敏光照 → 滑动平均滤波 → 写入 DataModel
 *   → 通知 DisplayTask 刷新显示
 */
#ifndef __TASK_SENSOR_H
#define __TASK_SENSOR_H

/* DisplayTask 等待的刷新标志位 */
#define DISPLAY_FLAG_REFRESH  (0x01UL)

/* 采集周期 ms */
#define SENSOR_PERIOD_MS      500U

/**
 * @brief 传感器采集任务入口
 * @param argument 未使用
 */
void TaskSensor(void *argument);

#endif /* __TASK_SENSOR_H */
