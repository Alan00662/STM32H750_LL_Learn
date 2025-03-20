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

#include "board.h"
#include "driver_led.h"


void MX_FREERTOS_Init(void);

int main(void)
{
//	SCB->VTOR=0x90000000;
	SCB_EnableICache();		// 使能ICache
	SCB_EnableDCache();		// 使能DCache
	boardInit();

  osKernelInitialize();

  MX_FREERTOS_Init();

  osKernelStart();

  while (1)
  {


  }

}



