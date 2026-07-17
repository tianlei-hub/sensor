/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "AHT20.h"
#include "getvoltage.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define K 30.0f //将获取光敏电阻的ADC值进行转化的相关参数
#define N 1.5f
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
float voltage_to_light(float voltage);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint8_t oled_light = 1;  // 1=亮, 0=灭
#define DEBOUNCE_MS  200   // 防抖时间200ms
// 每个按键独立的防抖计时器
uint32_t last_tick_switch = 0;  // SWITCH按键防抖
uint32_t last_tick_speed  = 0;  // SPEED按键防抖
uint32_t last_tick_light  = 0;  // LIGHT按键防抖
uint8_t fan_frame = 0;  // 当前风扇帧
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_ADC3_Init();
  MX_TIM12_Init();
  /* USER CODE BEGIN 2 */
HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_RESET);
  AHT20_Init();
  HAL_Delay(40);
  OLED_Init();
__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 0);  //先确保占空比为0
  HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
  
 //HAL_GPIO_WritePin(PWM_GPIO_Port,PWM_Pin,GPIO_PIN_RESET);
  char tmp[20]={};
  char hum[20]={};
  float LS1_voltage=0.0f;
  float LS1=0.0f;
  char LS1_msg[20]={};
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    LS1_voltage=Get_Voltage(&hadc3);//获取光敏传感器电压值
     LS1=voltage_to_light(LS1_voltage);
     sprintf(LS1_msg,"光照:%0.1f",100-LS1);
      
     //////////////////////
     AHT20_measure();
     AHT20_get_data();
      //
     sprintf(tmp,"温度:%0.1f℃",temperature);
     sprintf(hum,"湿度:%0.1f%%",humidity);
    ////////////////////////////
    OLED_NewFrame();
      if(__HAL_TIM_GET_COMPARE(&htim12,TIM_CHANNEL_1)!=0)
      {
          switch(fan_frame)
            {
            case 0:OLED_DrawImage(70,2,&fan0Img,OLED_COLOR_NORMAL);break;
            case 1:OLED_DrawImage(70,2,&fan1Img,OLED_COLOR_NORMAL);break;
            }
      }
      else
      {
          OLED_DrawImage(70,2,&fan0Img,OLED_COLOR_NORMAL);
      }
    fan_frame++;
    if (fan_frame > 1)
        fan_frame = 0;
    //OLED_DrawImage(5,40,&sunImg,OLED_COLOR_NORMAL);
    //OLED_DrawImage(20,40,&moonImg,OLED_COLOR_NORMAL);
    OLED_PrintString(2,38,LS1_msg,&font12x12,OLED_COLOR_NORMAL);//打印光照强度
     
    OLED_PrintString(2, 2,tmp, &font12x12, OLED_COLOR_NORMAL);
    OLED_PrintString(2, 20,hum, &font12x12, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
    HAL_Delay(500);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
float voltage_to_light(float voltage)
{
    float lux = K * powf(voltage, N);
    // 限幅到 0~100
    if (lux > 100) lux = 100;
    if (lux < 0)   lux = 0;
    return lux;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    // ---- SWITCH 按键：风扇 开/关 切换 ----
    if (GPIO_Pin == SWITCH_Pin)
    {
        if (now - last_tick_switch < DEBOUNCE_MS) return;
        last_tick_switch = now;

        if (__HAL_TIM_GET_COMPARE(&htim12, TIM_CHANNEL_1) == 0)
        {
            __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 4199);  // 全速
        }
        else
        {
            __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 0);     // 关闭
        }
    }

    // ---- SPEED 按键：风扇半速 / 全速切换 ----
    if (GPIO_Pin == SPEED_Pin)
    {
        if (now - last_tick_speed < DEBOUNCE_MS) return;
        last_tick_speed = now;

        uint32_t cmp = __HAL_TIM_GET_COMPARE(&htim12, TIM_CHANNEL_1);

        if (cmp == 0)
        {
            // 当前关闭 → 启动半速
            __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 2100);
        }
        else if (cmp <= 2100)
        {
            // 当前半速 切换全速
            __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 4199);
        }
        else
        {
            // 当前全速 切换半速
            __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 2100);
        }
    }

    // ---- LIGHT 按键：OLED 亮/灭 切换 
    if (GPIO_Pin == LIGHT_Pin)
    {
        if (now - last_tick_light < DEBOUNCE_MS) return;
        last_tick_light = now;

        oled_light = !oled_light;
        if (oled_light)
        {
            OLED_DisPlay_On();
        }
        else
        {
            OLED_DisPlay_Off();
        }
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
