/**
 * @file    task_display.h
 * @brief   OLED 显示任务
 *
 * 等待 SensorTask 的刷新通知 → 读 DataModel → 绘制温度/湿度/光照/风扇动画
 * LIGHT 键切换显示开关，关闭时跳过绘制
 */
#ifndef __TASK_DISPLAY_H
#define __TASK_DISPLAY_H

/**
 * @brief OLED 显示任务入口
 * @param argument 未使用
 */
void TaskDisplay(void *argument);

#endif /* __TASK_DISPLAY_H */
