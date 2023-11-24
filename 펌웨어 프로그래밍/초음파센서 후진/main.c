/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define STK_CTRL  *(volatile unsigned int*)0xE000E010
#define STK_LOAD  *(volatile unsigned int*)0xE000E014
#define STK_VAL   *(volatile unsigned int*)0xE000E018
#define STK_CALIB *(volatile unsigned int*)0xE000E01c
   
#define ENABLE 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
FILE __stdout;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int fputc(int ch, FILE* stream)
{
 HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 0xffff);
 return ch;
}
void usDelay(uint16_t us);
void SysTic_Init();
void HAL_Delay_Porting();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main()
{
	
  uint16_t cnt = 0;
  uint32_t echoTime = 0;
	uint32_t pwmF;
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  
	MX_TIM1_Init();
	MX_TIM3_Init();
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_Base_Start(&htim1);
  HAL_TIM_Base_Start(&htim3);
	TIM1->EGR = TIM1->EGR | 0x01;
   
  while(1){
   
     SysTic_Init();
     //구현파 발생 조건
     HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, 1);
     usDelay(15);
     HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, 0);
      
     while(HAL_GPIO_ReadPin(Echo_GPIO_Port, Echo_Pin) == 0);         
     STK_CTRL |= (1 << ENABLE);               //SysTick timer start
     while(HAL_GPIO_ReadPin(Echo_GPIO_Port, Echo_Pin) == 1);
     echoTime = HAL_GetTick();
     STK_CTRL &= ~(1 << ENABLE);
     //340m/s -> 340 * 100cm/1000000us -> 0.034cm/u s
      
		 printf("Distance = %.1lf cm\n\r", echoTime / 2 * 0.034);
  
		 
     HAL_Delay_Porting();
     HAL_Delay(200);
		
		 if ( 0.0 < (echoTime / 2 * 0.034) && (echoTime / 2 * 0.034) < 10.0) {
			 pwmF = 10000000 / 523;
			 TIM1 -> ARR = pwmF -1;
			 TIM1 -> CCR2 = pwmF / 2;
			 HAL_Delay(100);
			 TIM1->ARR = 0; 
			 TIM1->CCR2 = 0;
		 }
		 else if ( 10.0 < (echoTime / 2 * 0.034) && (echoTime / 2 * 0.034) < 20.0) {
			 pwmF = 10000000 / 523;
			 TIM1 -> ARR = pwmF -1;
			 TIM1 -> CCR2 = pwmF / 2;
			 HAL_Delay(300);
			 TIM1->ARR = 0; 
			 TIM1->CCR2 = 0;
		 }
   }
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
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void usDelay(uint16_t us){
      __HAL_TIM_SET_COUNTER(&htim3, 0);   //TIM3 init
      while(__HAL_TIM_GET_COUNTER(&htim3) < us){
      
      }
}

void SysTic_Init()
{
   STK_LOAD = 100 - 1;
   STK_VAL = 0;
   STK_CTRL = 6; 
   uwTick = 0;
}

void HAL_Delay_Porting()
{
   STK_LOAD = 100000 - 1;
   STK_CTRL |= 7;
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

#ifdef  USE_FULL_ASSERT
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
