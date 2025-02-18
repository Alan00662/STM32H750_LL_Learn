/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
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
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */
#define QSPI_CS_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOG_CLK_ENABLE()//注意修改启动的时钟源
#define QSPI_CLK_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()//注意修改启动的时钟源
#define QSPI_BK1_D0_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()//注意修改启动的时钟源
#define QSPI_BK1_D1_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()//注意修改启动的时钟源
#define QSPI_BK1_D2_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()//注意修改启动的时钟源
#define QSPI_BK1_D3_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()//注意修改启动的时钟源

#define QSPI_FORCE_RESET()              __HAL_RCC_QSPI_FORCE_RESET()
#define QSPI_RELEASE_RESET()            __HAL_RCC_QSPI_RELEASE_RESET()

#define QSPI_CS_PIN                     GPIO_PIN_6 //QSPI_CS
#define QSPI_CS_GPIO_PORT               GPIOG
#define QSPI_CS_GPIO_AF                 GPIO_AF10_QUADSPI//有坑，自行比较CubeMX生成的正确指向

#define QSPI_CLK_PIN                    GPIO_PIN_10 //QSPI_CLK
#define QSPI_CLK_GPIO_PORT              GPIOF
#define QSPI_CLK_GPIO_AF                GPIO_AF9_QUADSPI//有坑，自行比较CubeMX生成的正确指向

#define QSPI_BK1_D0_PIN                 GPIO_PIN_8 //QSPI_BK1_D0
#define QSPI_BK1_D0_GPIO_PORT           GPIOF
#define QSPI_BK1_D0_GPIO_AF             GPIO_AF10_QUADSPI//有坑，自行比较CubeMX生成的正确指向

#define QSPI_BK1_D1_PIN                 GPIO_PIN_9 //QSPI_BK1_D1
#define QSPI_BK1_D1_GPIO_PORT           GPIOF
#define QSPI_BK1_D1_GPIO_AF             GPIO_AF10_QUADSPI//有坑，自行比较CubeMX生成的正确指向

#define QSPI_BK1_D2_PIN                 GPIO_PIN_7 //QSPI_BK1_D2
#define QSPI_BK1_D2_GPIO_PORT           GPIOF
#define QSPI_BK1_D2_GPIO_AF             GPIO_AF9_QUADSPI//有坑，自行比较CubeMX生成的正确指向

#define QSPI_BK1_D3_PIN                 GPIO_PIN_6 //QSPI_BK1_D3
#define QSPI_BK1_D3_GPIO_PORT           GPIOF
#define QSPI_BK1_D3_GPIO_AF             GPIO_AF9_QUADSPI//有坑，自行比较CubeMX生成的正确指向

/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

