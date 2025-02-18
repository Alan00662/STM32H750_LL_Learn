/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
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
#include "quadspi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 2;
  hqspi.Init.FifoThreshold = 32;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 24;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_5_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

	
	
	
  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct;
/* 使能QPSI时钟  */
    __HAL_RCC_QSPI_CLK_ENABLE();
/* 复位时钟接口 */
    QSPI_FORCE_RESET();
    QSPI_RELEASE_RESET();    
/* 使能GPIO时钟 */
	
    QSPI_CS_GPIO_CLK_ENABLE();
    QSPI_CLK_GPIO_CLK_ENABLE();
    QSPI_BK1_D0_GPIO_CLK_ENABLE();
    QSPI_BK1_D1_GPIO_CLK_ENABLE();
    QSPI_BK1_D2_GPIO_CLK_ENABLE();
    QSPI_BK1_D3_GPIO_CLK_ENABLE();
	
	
/* QSPI CS GPIO 引脚配置 */
    GPIO_InitStruct.Pin = QSPI_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//这句代码不能少
    GPIO_InitStruct.Alternate = QSPI_CS_GPIO_AF;//有坑
    HAL_GPIO_Init(QSPI_CS_GPIO_PORT, &GPIO_InitStruct);
		
/* QSPI CLK GPIO 引脚配置 */
    GPIO_InitStruct.Pin = QSPI_CLK_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//这句代码不能少
    GPIO_InitStruct.Alternate = QSPI_CLK_GPIO_AF;//有坑
    HAL_GPIO_Init(QSPI_CLK_GPIO_PORT, &GPIO_InitStruct);
		
/* QSPI D0 GPIO pin 引脚配置 */
    GPIO_InitStruct.Pin = QSPI_BK1_D0_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//这句代码不能少
    GPIO_InitStruct.Alternate = QSPI_BK1_D0_GPIO_AF;//有坑
    HAL_GPIO_Init(QSPI_BK1_D0_GPIO_PORT, &GPIO_InitStruct);
		
/* QSPI D1 GPIO 引脚配置 */
    GPIO_InitStruct.Pin = QSPI_BK1_D1_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//这句代码不能少
    GPIO_InitStruct.Alternate = QSPI_BK1_D1_GPIO_AF;//有坑
    HAL_GPIO_Init(QSPI_BK1_D1_GPIO_PORT, &GPIO_InitStruct);
		
/* QSPI D2 GPIO 引脚配置 */
    GPIO_InitStruct.Pin = QSPI_BK1_D2_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//这句代码不能少
    GPIO_InitStruct.Alternate = QSPI_BK1_D2_GPIO_AF;//有坑
    HAL_GPIO_Init(QSPI_BK1_D2_GPIO_PORT, &GPIO_InitStruct);
		
/* QSPI D3 GPIO 引脚配置 */
    GPIO_InitStruct.Pin = QSPI_BK1_D3_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//这句代码不能少
    GPIO_InitStruct.Alternate = QSPI_BK1_D3_GPIO_AF;//有坑
    HAL_GPIO_Init(QSPI_BK1_D3_GPIO_PORT, &GPIO_InitStruct);
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

    /* 复位QSPI引脚 */
    HAL_GPIO_DeInit(QSPI_CS_GPIO_PORT, QSPI_CS_PIN);
    HAL_GPIO_DeInit(QSPI_CLK_GPIO_PORT, QSPI_CLK_PIN);
    HAL_GPIO_DeInit(QSPI_BK1_D0_GPIO_PORT, QSPI_BK1_D0_PIN);
    HAL_GPIO_DeInit(QSPI_BK1_D1_GPIO_PORT, QSPI_BK1_D1_PIN);
    HAL_GPIO_DeInit(QSPI_BK1_D2_GPIO_PORT, QSPI_BK1_D2_PIN);
    HAL_GPIO_DeInit(QSPI_BK1_D3_GPIO_PORT, QSPI_BK1_D3_PIN);

    /* 复位QSPI */
    QSPI_FORCE_RESET();
    QSPI_RELEASE_RESET();

    /* 关闭QSPI时钟 */
    __HAL_RCC_QSPI_CLK_DISABLE();
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
