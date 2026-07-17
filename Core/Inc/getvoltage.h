#ifndef __GETVOLTAGE_H__
#define __GETVOLTAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


void Voltage_Init(ADC_HandleTypeDef *hadc);

float Get_Voltage(ADC_HandleTypeDef *hadc);



#ifdef __cplusplus
}
#endif
#endif