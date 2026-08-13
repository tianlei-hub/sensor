/**
 * @file    data_filter.h
 * @brief   滑动平均滤波器
 * @note    用于滤除传感器瞬时噪声，窗口越小响应越快
 */
#ifndef __DATA_FILTER_H
#define __DATA_FILTER_H

#include <stdint.h>

#define FILTER_WINDOW_SIZE 5   /* 滑动窗口大小 */

typedef struct {
    float  buffer[FILTER_WINDOW_SIZE];
    uint8_t index;
    uint8_t count;   /* 当前已填入的样本数（小于窗口时直接输出均值） */
} FilterHandle_t;

/**
 * @brief 初始化滤波器（清零窗口）
 * @param[in,out] f 滤波器句柄
 */
void Filter_Init(FilterHandle_t *f);

/**
 * @brief 输入新样本，输出滤波结果
 * @param[in,out] f     滤波器句柄
 * @param[in]     value 新样本
 * @retval 滤波后的值
 */
float Filter_Update(FilterHandle_t *f, float value);

#endif /* __DATA_FILTER_H */
