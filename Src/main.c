/**
  ******************************************************************************
  * @file    STM32F4_MAX7219/Src/main.c 
  * @author  thzvm
  * @brief   Main program body
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "max7219.h"

/* Private typedef -----------------------------------------------------------*/
SPI_HandleTypeDef hspi4;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void GPIO_Init(void);
static void SPI4_Init(void);

/* Private functions ---------------------------------------------------------*/
int main (void){
  
  HAL_Init();
  SystemClock_Config();
  GPIO_Init();
  SPI4_Init();
  MAX7219_Init();
  
  while (1){
   
    MAX7219_SendByte(MAX7219_DIG_0, MAX7219_CodeB_0);
    MAX7219_SendByte(MAX7219_DIG_1, MAX7219_CodeB_dash);
    MAX7219_SendByte(MAX7219_DIG_2, MAX7219_CodeB_4);
    MAX7219_SendByte(MAX7219_DIG_3, MAX7219_CodeB_7);  
    MAX7219_SendByte(MAX7219_DIG_4, MAX7219_CodeB_1|MAX7219_CodeB_dot);   
    HAL_Delay(500);     
  }
}

/** System Clock Configuration*/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  
  //Configure the main internal regulator output voltage
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  //Initializes the CPU, AHB and APB busses clock
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
    _Error_Handler(__FILE__, __LINE__);
  }
  
  //Initializes the CPU, AHB and APB busses clocks
   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK){
    _Error_Handler(__FILE__, __LINE__);
  }
  
  // Configure the Systick interrupt time
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  
  // Configure the Systick
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  
  // SysTick_IRQn interrupt configuration 
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI4 init function */
static void SPI4_Init(void){
  
  // SPI4 parameter configuration
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 10;
  
  if (HAL_SPI_Init(&hspi4) != HAL_OK){
    _Error_Handler(__FILE__, __LINE__);
  }
}

/* GPIO init function */
static void GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  // GPIO Ports Clock Enable
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  // Configure GPIO pin Output Level
  HAL_GPIO_WritePin(SPI4_PORT, SPI4_CS, GPIO_PIN_RESET);

  // Configure GPIO pin : PE11 (NSS)
  GPIO_InitStruct.Pin = SPI4_CS;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void _Error_Handler(char *file, int line)
{
  while(1)
  {
  }

}
