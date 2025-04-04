/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_ll_adc.h"
#include "stm32h7xx_ll_dma.h"
#include "stm32h7xx_ll_dma2d.h"
#include "stm32h7xx_ll_i2c.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_crs.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_exti.h"
#include "stm32h7xx_ll_cortex.h"
#include "stm32h7xx_ll_utils.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_tim.h"
#include "stm32h7xx_ll_usart.h"
#include "stm32h7xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENTER_Pin LL_GPIO_PIN_12
#define ENTER_GPIO_Port GPIOG
#define MDL_Pin LL_GPIO_PIN_3
#define MDL_GPIO_Port GPIOE
#define LED0_Pin LL_GPIO_PIN_8
#define LED0_GPIO_Port GPIOI
#define PAGE_R_Pin LL_GPIO_PIN_8
#define PAGE_R_GPIO_Port GPIOA
#define LED1_Pin LL_GPIO_PIN_10
#define LED1_GPIO_Port GPIOI
#define LED2_Pin LL_GPIO_PIN_11
#define LED2_GPIO_Port GPIOI
#define PAGE_L_Pin LL_GPIO_PIN_7
#define PAGE_L_GPIO_Port GPIOG
#define RTN_Pin LL_GPIO_PIN_3
#define RTN_GPIO_Port GPIOG
#define TELE_Pin LL_GPIO_PIN_2
#define TELE_GPIO_Port GPIOG
#define SYS_Pin LL_GPIO_PIN_2
#define SYS_GPIO_Port GPIOB
#define PWR_Pin LL_GPIO_PIN_12
#define PWR_GPIO_Port GPIOH
#define PWR_KEY_Pin LL_GPIO_PIN_4
#define PWR_KEY_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
uint32_t millis(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
