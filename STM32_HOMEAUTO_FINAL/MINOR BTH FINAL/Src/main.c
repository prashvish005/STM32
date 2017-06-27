#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                
int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
	
	char mydata[18] = "System Operational";
	
	//char rec[500];
	char recb[500];
	
  char AT_0[6] =  "AT\r\n";
	char AT_1[10] = "AT+RST\r\n";
	char AT_2[15] = "AT+CWMODE=3\r\n";
	char AT_3[12] = "AT+CIFSR\r\n";
	char AT_4[15] = "AT+CIPMUX=1\r\n";
	char AT_5[21] = "AT+CIPSERVER=1,80\r\n";
	char AT_6[39] = "AT+CWJAP=\"Alpharage\",\"09071995\"\r\n";
	char AT_7[47] = "AT+CIPSTART=\"TCP\",\"www.iotprash.com\",80\r\n";
	char AT_8[17] = "AT+CIPSEND=63\r\n";
	char AT_9[28] = "GET /light.json HTTP/1.1\r\n";
	char AT_10[33] = "Host: www.iotprash.com:80\r\n\r\n";
	char AT_11[12] = "\r\n\r\n\r\n\r\n";
  
	int m11;
	int m12;
	int m21;
	int m22;
	int m31;
	int m32;
	int m41;
	int m42;
	int dim1;
	int dim2;
	int dim3;
	int dim4;
	int pwm=0;
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	
	HAL_UART_Transmit(&huart2, (uint8_t *)mydata, 18, 50);
	
	/* HAL_UART_Transmit(&huart3, (uint8_t *)AT_1, 10, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 1000);
	//HAL_Delay(5000);
	// HAL_UART_Transmit(&huart3, (uint8_t *)AT_2, 15, 1000);
	// HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 2000);
	// HAL_Delay(5000);
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_3, 12, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 1000);
	//HAL_Delay(5000);
	// HAL_UART_Transmit(&huart3, (uint8_t *)AT_4, 15, 1000);
	// HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 2000);
	// HAL_Delay(5000);
	// HAL_UART_Transmit(&huart3, (uint8_t *)AT_5, 25, 1000);
	// HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 2000);
	// HAL_Delay(5000);	
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_6, 39, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 1000);
	HAL_Delay(1500);
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_7, 47, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 1000);
	HAL_Delay(500);
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_8, 17, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 1000);
	HAL_Delay(500);
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_9, 28, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 1000);
	HAL_Delay(500);
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_10, 33, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 1000);
	HAL_Delay(500);	
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_11, 12, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 1000);
	HAL_Delay(500);	
	*/
	
  while (1)
  { 
	  /*HAL_UART_Transmit(&huart3, (uint8_t *)AT_7, 47, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 2000);
	//HAL_Delay(500);
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_8, 17, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 2000);
	//HAL_Delay(500);
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_9, 28, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 2000);
	//HAL_Delay(500);
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_10, 33, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 2000);
	//HAL_Delay(500);	
	HAL_UART_Transmit(&huart3, (uint8_t *)AT_11, 12, 500);
	HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 2000);
	//HAL_Delay(500);	
	  */
		HAL_UART_Receive(&huart3, (uint8_t *)recb, 500, 500);
		HAL_UART_Receive(&huart2, (uint8_t *)recb, 50, 1000);
	  m11=strncmp(recb,"*switch on#",11);
		m12=strncmp(recb,"*switch off#",12);
		m21=strncmp(recb,"*lamp on#",9);
		m22=strncmp(recb,"*lamp of#",9);
		m31=strncmp(recb,"*all on#",8);
		m32=strncmp(recb,"*all of#",8);
		m41=strncmp(recb,"*plug on#",9);
		m42=strncmp(recb,"*plug off#",10);
		dim1=strncmp(recb,"*lamp 1#",8);
		dim2=strncmp(recb,"*lamp 2#",8);
		dim3=strncmp(recb,"*lamp 3#",8);
		dim4=strncmp(recb,"*lamp 4#",8);

		
		if(m11==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		}
		else if(m12==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		}
		else if(m21==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
		}
		else if(m22==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		}
		else if(m31==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		}
		else if(m32==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		}
		else if(m41==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		}
		else if(m42==0)
		{
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		}
		else if(dim1==0)
		{
			pwm=0;
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pwm);
			HAL_Delay(10);
		}
		else if(dim2==0)
		{
			pwm=30;
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pwm);
			HAL_Delay(10);
		}
		else if(dim3==0)
		{
			pwm=70;
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pwm);
			HAL_Delay(10);
		}
		else if(dim4==0)
		{
			pwm=200;
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pwm);
			HAL_Delay(10);
		}
		else
		{
		 HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
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

static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 24;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 200;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim3);

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

static void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13 
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13 
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

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