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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
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
#define TEMP 0
#define HUMI 1

#define SHT20_ADDR				(0x40 << 1)
#define HOLD_MASTER_T			0xE3
#define HOLD_MASTER_H			0xE5
#define NO_HOLD_MASTER_T 	0xF3
#define NO_HOLD_MASTER_RH	0xF5
#define WRITE_USER_RE			0xE6
#define READ_USER_RE			0xE7
#define SOFT_RESET				0xFE
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
FILE __stdout;

uint8_t rxData;
uint16_t LAMPData[2];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int fputc(int ch, FILE* stream)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 0xffff);
	return ch;
}

float sht20(int);
void sht20_INIT();
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
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_I2C1_Init();
	MX_USART2_UART_Init();
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) LAMPData, 1);
	HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
	
	MX_TIM1_Init();
	MX_TIM3_Init();
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	
	void MENU();
	void LEDSHIFT();
	void MOOD();
	void PIANO();
	void STREETLIGHT();
	void num5play();
	
	sht20_INIT();
	uint16_t scale[] = {523, 587, 659, 698, 783, 880, 987, 1046};
	uint32_t pwmF;
	
	MENU();
	
	while(1)
	{
		HAL_Delay(500);
		
		//LED 옮기기
		if(rxData == '1')
		{
			LEDSHIFT();
		}
		
		//무드등
		if(rxData == '2')
		{
			MOOD();
		}
		
		//피아노
		if(rxData == '3')
		{
			PIANO();
		}
		
		//가로등
		if(rxData == '4')
		{
			STREETLIGHT();
		}		
		
		//온도 습도
		if(rxData == '5')
		{
			num5play();
		}
		
		//프로그램 종료
		if(rxData == '0')
		{
			printf("********************Shut down the program********************\r\n");
			break;
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2){
		HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
	}
}
void MENU(void)
{
	printf("********************EMBEDDED SYSTEM********************\r\n");
	printf("1. LED_SHIFT\r\n2. MOOD_LIGHT\r\n3. PIANO\r\n4. STREETLIGHT\r\n5. TEMP/HUMI\r\n0. EXIT\r\n");
}
void LEDSHIFT()
{
	printf("LED_SHIFT START\r\n");
	printf("a = DOWN_SHIFT\r\ns = UP_SHIFT\r\nd = LED_STOP\r\nz = BACK TO The MENU\r\n");
	int i = 0;
	int LED = 1;
	while(1) 
		{
			HAL_Delay(500);
			
			if(rxData == 'a')
			{
				HAL_GPIO_WritePin(GPIOC, LED << i, 1);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOC, LED << i, 0);
				i++;
				if(i == 9)	{i = 0;}
			}
		
			if(rxData == 's')
			{
				HAL_GPIO_WritePin(GPIOC, LED << i, 1);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOC, LED << i, 0);
				i--;
				if (i < 0){i = 9;}
			}
		
			if(rxData ==  'd')
			{
				i = i;
				HAL_GPIO_WritePin(GPIOC, LED << i, 1);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOC, LED << i, 0);
			}
			if(rxData == 'z')
			{
				MENU();
				break;
			}
		}		
}

void MOOD(void)
{
	uint32_t LAMP = 0;
	int direction = 5;

	printf("MOODLAMP START\r\nz = BACK TO The MENU\r\n");
	while(1)
	{
		TIM1->CCR2 = LAMP;
		HAL_Delay(100);
		LAMP += direction;
		if(LAMP >= 50 || LAMP <=0)
		{
			direction = -direction;
		}
		
    if (rxData == 'z')
    {
			TIM1->CCR2 = 0;
      MENU();
      break;
    }
        
	}
}
void PIANO(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	printf("PIANO START\r\nz = BACK TO The MENU\r\n");
	printf("q = A  w = B  e = C  r = D  t = E  y = F  u = G  i = A\r\n");

	while(1)
	{
		uint32_t pwmF;
		uint16_t scale[] = {523, 587, 659, 698, 783, 880, 987, 1046};
		TIM3->EGR = TIM3->EGR | 0x01;
		HAL_Delay(500);
		
		if(rxData == 'q')
		{
			printf("NOW : %c\r\n", rxData);
			pwmF = 10000000 / scale[0]; 
			TIM3->ARR = pwmF - 1;
			TIM3->CCR1 = pwmF / 2;
			HAL_Delay(200);
			TIM3->ARR = 0; 
			TIM3->CCR1 = 0;
			rxData = 0;
		}
		if(rxData == 'w')
		{
			printf("NOW : %c\r\n", rxData);
			pwmF = 10000000 / scale[1]; 
			TIM3->ARR = pwmF - 1;
			TIM3->CCR1 = pwmF / 2;
			HAL_Delay(200);
			TIM3->ARR = 0; 
			TIM3->CCR1 = 0;
			rxData = 0;
		}
		if(rxData == 'e')
		{
			printf("NOW : %c\r\n", rxData);
			pwmF = 10000000 / scale[2]; 
			TIM3->ARR = pwmF - 1;
			TIM3->CCR1 = pwmF / 2;
			HAL_Delay(200);
			TIM3->ARR = 0; 
			TIM3->CCR1 = 0;
			rxData = 0;
		}
		if(rxData == 'r')
		{
			printf("NOW : %c\r\n", rxData);
			pwmF = 10000000 / scale[3]; 
			TIM3->ARR = pwmF - 1;
			TIM3->CCR1 = pwmF / 2;
			HAL_Delay(200);
			TIM3->ARR = 0; 
			TIM3->CCR1 = 0;
			rxData = 0;
		}
		if(rxData == 't')
		{
			printf("NOW : %c\r\n", rxData);
			pwmF = 10000000 / scale[4]; 
			TIM3->ARR = pwmF - 1;
			TIM3->CCR1 = pwmF / 2;
			HAL_Delay(200);
			TIM3->ARR = 0; 
			TIM3->CCR1 = 0;
			rxData = 0;
		}
		if(rxData == 'y')
		{
			printf("NOW : %c\r\n", rxData);
			pwmF = 10000000 / scale[5]; 
			TIM3->ARR = pwmF - 1;
			TIM3->CCR1 = pwmF / 2;
			HAL_Delay(200);
			TIM3->ARR = 0; 
			TIM3->CCR1 = 0;
			rxData = 0;
		}
		if(rxData == 'u')
		{
			printf("NOW : %c\r\n", rxData);
			pwmF = 10000000 / scale[6]; 
			TIM3->ARR = pwmF - 1;
			TIM3->CCR1 = pwmF / 2;
			HAL_Delay(200);
			TIM3->ARR = 0; 
			TIM3->CCR1 = 0;
			rxData = 0;
		}
		if(rxData == 'i')
		{
			printf("NOW : %c\r\n", rxData);
			pwmF = 10000000 / scale[7]; 
			TIM3->ARR = pwmF - 1;
			TIM3->CCR1 = pwmF / 2;
			HAL_Delay(200);
			TIM3->ARR = 0; 
			TIM3->CCR1 = 0;
			rxData = 0;
		}
		if(rxData == 'z')
		{
			MENU();
			break;
		}
	}
}
void STREETLIGHT()
{
	printf("STREETLIGHT START\r\nz = BACK TO The MENU\r\n");
	while(1)
	{
		printf("ADC : %d\n\r", LAMPData[0]);
		HAL_Delay(1000);
		
		if (LAMPData[0] >= 3000)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, 0);
			HAL_Delay(500);
		}
		if (LAMPData[0] <= 2500 && LAMPData[0] > 1000)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 1);
			HAL_Delay(500);
		}
		if (LAMPData[0] <=1000)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, 1);
			HAL_Delay(500);
		}
		if(rxData == 'z')
		{
			MENU();
			break;
		}
	}
}
void sht20_INIT(void)
{
	if(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SHT20_ADDR, (uint8_t*)SOFT_RESET, 1, 0xffff) == HAL_OK)
   {
      printf("SHT20 RESET FAIL!!\n\r");
   }
   else{
      printf("SHT20 RESET SUCCESS!!\n\r");
   }
}	

float sht20(int choose)
{	
		uint16_t shDATA[3];
		uint16_t sensor;
		float conv = 0.0;
		
	if (choose == TEMP)
		{
			shDATA[0] = HOLD_MASTER_T;
			HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SHT20_ADDR, (uint8_t*)shDATA, 1, 0xffff);
			HAL_Delay(100);
			HAL_I2C_Master_Receive(&hi2c1, (uint16_t)SHT20_ADDR, (uint8_t*)shDATA, 2, 0xffff);
			sensor = shDATA[0] << 8 | shDATA[1];
			conv = -46.85 + 175.72 / 65536 * (float)sensor;
		}
		if (choose == HUMI)
		{
			shDATA[0] = HOLD_MASTER_H;
			HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SHT20_ADDR, (uint8_t*)shDATA, 1, 0xffff);
			HAL_Delay(100);
			HAL_I2C_Master_Receive(&hi2c1, (uint16_t)SHT20_ADDR, (uint8_t*)shDATA, 2, 0xffff);
			sensor = shDATA[0] << 8 | shDATA[1];
			conv = -6.0 + 125.0 / 65536 * (float)sensor;
		}
		return conv;	
	
		
}
void num5play()
{
	float temperature, humidity;
	while(1)
	{
		temperature	=	sht20(TEMP);
		humidity = sht20(HUMI);
		printf("TEMP = %.2lf  HUMI = %.2lf\n\r", temperature, humidity);
		HAL_Delay(500);
		if(rxData == 'z')
		{
			MENU();
			break;
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
