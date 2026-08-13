/**
 * @file    task_fan.h
 * @brief   风扇控制任务
 *
 * 事件驱动：等待按键事件队列 → 状态机转移 → PWM 输出
 * 按键链路：EXTI ISR → 消息队列 → 本任务（消抖在 ISR 完成）
 */
#ifndef __TASK_FAN_H
#define __TASK_FAN_H

/**
 * @brief 风扇控制任务入口
 * @param argument 未使用
 */
void TaskFan(void *argument);

#endif /* __TASK_FAN_H */
