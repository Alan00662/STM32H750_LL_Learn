/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "cmsis_os.h"
#include "adc.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "memorymap.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"


#include "driver_led.h"
#include "driver_system_clock.h"

void MX_FREERTOS_Init(void);

int main(void)
{

  MPU_Config();

  HAL_Init();

  SystemClock_Config();

  PeriphCommonClock_Config();

  MX_GPIO_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_LTDC_Init();
  MX_DMA2D_Init();
  MX_I2C4_Init();
  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_FMC_Init();

  osKernelInitialize();

  MX_FREERTOS_Init();

  osKernelStart();

  while (1)
  {


  }

}



