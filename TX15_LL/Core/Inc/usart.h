/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_UART5_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void uart1_send_string(char *str);
void uart1_send_buf(uint8_t *buf, uint8_t len);
void debug_tx1(char *fmt, ...);
void uart2_send_string(char *str);
void uart2_send_buf(uint8_t *buf, uint8_t len);
void debug_tx2(char *fmt, ...);
void uart3_send_string(char *str);
void uart3_send_buf(uint8_t *buf, uint8_t len);
void debug_tx3(char *fmt, ...);
void uart4_send_string(char *str);
void uart4_send_buf(uint8_t *buf, uint8_t len);
void debug_tx4(char *fmt, ...);
void uart5_send_a_byte(uint8_t Data);
void uart5_send_string(char *str);
void uart5_send_buf(uint8_t *buf, uint8_t len);
void debug_tx5(char *fmt, ...);
void uart6_send_byte(uint8_t Data);
void uart6_send_string(char *str);
void uart6_send_buf(uint8_t *buf, uint8_t len);
void debug_tx6(char *fmt, ...);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

