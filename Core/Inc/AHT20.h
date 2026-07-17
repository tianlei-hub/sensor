#ifndef __AHT20_H__
#define __AHT20_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"
#include <stdio.h>
#include <string.h>
//#define AHT20_USE_UART

#define AHT20_I2C_HANDLE   hi2c2
//#define AHT20_UART_HANDLE  huart1

extern I2C_HandleTypeDef AHT20_I2C_HANDLE;
//extern UART_HandleTypeDef AHT20_UART_HANDLE;

extern float temperature;
extern float humidity;
extern char message_tmp[40];
extern char message_hum[40];
    
#define AHT20_ADDRESS (0x38<<1)
#define AHT20_RESET 0xBA

void AHT20_Init(void);
void AHT20_measure(void);
void AHT20_get_data(void);

void prinf_tmp(void);
void prinf_hum(void);


#ifdef __cplusplus
}
#endif
#endif