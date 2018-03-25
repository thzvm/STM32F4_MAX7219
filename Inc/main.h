/**
  ******************************************************************************
  * @file    STM32F4_MAX7219/Inc/main.h 
  * @author  thzvm
  * @brief   Header for main.c module
  *
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MAIN_H_
#define MAIN_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported constants --------------------------------------------------------*/
#define SPI4_PORT   GPIOE
#define SPI4_CS     GPIO_PIN_11
#define SPI4_SCK    GPIO_PIN_12
#define SPI4_MISO   GPIO_PIN_13
#define SPI4_MOSI   GPIO_PIN_14

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_ */
