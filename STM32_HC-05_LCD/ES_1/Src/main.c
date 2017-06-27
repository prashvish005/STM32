#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "STM_MY_LCD16X2.h"
UART_HandleTypeDef huart2;


void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);


int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
	
	char mydata[18] = "System Operational";
	char rec[50];
	int m11;
	int m12;
	int m21;
	int m22;
	int m31;
	int m32;
	int m41;
	int m42;
	int m51;
	int m52;
	
	HAL_UART_Transmit(&huart2, (uint8_t *)mydata, 18, 50);

  while (1)
  {
		HAL_UART_Receive(&huart2, (uint8_t *)rec, 50, 1000);
	  m11=strncmp(rec,"*switch on#",11);
		m12=strncmp(rec,"*switch off#",12);
		m21=strncmp(rec,"*lamp on#",9);
		m22=strncmp(rec,"*lamp of#",9);
		m31=strncmp(rec,"*all on#",8);
		m32=strncmp(rec,"*all of#",8);
		m41=strncmp(rec,"*plug on#",9);
		m42=strncmp(rec,"*plug off#",10);
		
		if(m11==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		}
		else if(m12==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		}
		else if(m21==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
		}
		else if(m22==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		}
		else if(m31==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		}
		else if(m32==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		}
		else if(m41==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		}
		else if(m42==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		}
		else
		{
		 HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_11);
     HAL_Delay(100);
		}	
  }

}

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

}

void Error_Handler(void)
{
  while(1) 
  {
  }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

}

#endif