#include "AHT20.h"

uint8_t AHT20_INIT=0xBE;
uint8_t  AHT20_STATUS=0x71;
uint8_t measure[3]={0xAC,0x33,0x00};

uint8_t status=0;
uint8_t data[6]={0};
uint32_t hum_raw=0;
uint32_t tmp_raw=0;

float temperature = 0;  
float humidity = 0; 


void AHT20_Init(void)
{
     HAL_Delay(40);
if(HAL_I2C_Master_Transmit(&AHT20_I2C_HANDLE,AHT20_ADDRESS,&AHT20_STATUS,1,100)==HAL_OK)
    {
        if(HAL_I2C_Master_Receive(&AHT20_I2C_HANDLE,AHT20_ADDRESS,&status,1,100)==HAL_OK)
        {
            if((status & 0x08)==0)
            {
                HAL_I2C_Master_Transmit(&AHT20_I2C_HANDLE,AHT20_ADDRESS,&AHT20_INIT,1,100);
            }
        }
    }   
}


void AHT20_measure(void)
{
    HAL_I2C_Master_Transmit(&AHT20_I2C_HANDLE,AHT20_ADDRESS,measure,3,100);
   
}

void AHT20_get_data(void)
{
     HAL_Delay(100);
          if(HAL_I2C_Master_Receive(&AHT20_I2C_HANDLE,AHT20_ADDRESS,data,6,100)==HAL_OK)
          {
              tmp_raw=((uint32_t)(data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];
              hum_raw=((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((data[3] & 0xF0) >> 4);
          }
          temperature=(tmp_raw/1048576.0f)*200-50;
          humidity=(hum_raw/1048576.0f)*100;
}


#ifdef AHT20_USE_UART

char message_tmp[40]={};
char message_hum[40]={};
void prinf_tmp(void)
{
    sprintf(message_tmp,"温度:%0.1f℃",temperature);
      HAL_UART_Transmit(&AHT20_UART_HANDLE,(uint8_t*)message_tmp,strlen(message_tmp),100);
}

void prinf_hum(void)
{
    sprintf(message_hum,"湿度:%0.1f%% \r\n",humidity);
      HAL_UART_Transmit(&AHT20_UART_HANDLE,(uint8_t*)message_hum,strlen(message_hum),100);
}
#endif