#include "getvoltage.h"

#define ADC_MAX 4096
#define VOLTAGE 3.3
#define ADC_TIMEOUT 100

void Voltage_Init(ADC_HandleTypeDef *hadc)
{
    HAL_ADC_Start(hadc);
}



float Get_Voltage(ADC_HandleTypeDef *hadc)
{
    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc,ADC_TIMEOUT);
    float ADC_Value=HAL_ADC_GetValue(hadc);
    
    HAL_ADC_Stop(hadc);
    return (ADC_Value*3.3)/4095;
}