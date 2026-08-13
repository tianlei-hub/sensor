/**
 * @file    data_filter.c
 * @brief   滑动平均滤波器实现
 */
#include "data_filter.h"
#include <string.h>

void Filter_Init(FilterHandle_t *f)
{
    if (f == NULL) return;
    memset(f, 0, sizeof(FilterHandle_t));
}

float Filter_Update(FilterHandle_t *f, float value)
{
    float sum = 0.0f;
    uint8_t i;
    uint8_t n;

    if (f == NULL) return value;

    /* 新样本入窗（环形覆盖） */
    f->buffer[f->index] = value;
    f->index = (f->index + 1) % FILTER_WINDOW_SIZE;
    if (f->count < FILTER_WINDOW_SIZE) {
        f->count++;
    }

    /* 求均值 */
    n = f->count;
    for (i = 0; i < n; i++) {
        sum += f->buffer[i];
    }
    return sum / (float)n;
}
