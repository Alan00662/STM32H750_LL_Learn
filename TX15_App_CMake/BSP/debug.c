#include "usart.h"
#include "board.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>



UART_HandleTypeDef uart_debug;




void Debug_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  DEBUG_CLK();

  GPIO_InitStruct.Pin = DEBUG_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = DEBUG_TX_AF;
  HAL_GPIO_Init(DEBUG_TX_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = DEBUG_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = DEBUG_RX_AF;
  HAL_GPIO_Init(DEBUG_RX_GPIO_Port, &GPIO_InitStruct);

  uart_debug.Instance = DEBUG_UART;
  uart_debug.Init.BaudRate = 115200;
  uart_debug.Init.WordLength = UART_WORDLENGTH_8B;
  uart_debug.Init.StopBits = UART_STOPBITS_1;
  uart_debug.Init.Parity = UART_PARITY_NONE;
  uart_debug.Init.Mode = UART_MODE_TX_RX;
  uart_debug.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  uart_debug.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&uart_debug) != HAL_OK)
  {
    Error_Handler();
  }


}

static void debug_string(char *str)
{
    uint8_t i;
    for (i = 0; i < strlen(str); i++) {
      HAL_UART_Transmit(&uart_debug, (uint8_t *)(str + i),1, 100);
    }
}
void Debug(const char *fmt, ...)
{
    char buf[200];

    va_list arguments;

    va_start(arguments, fmt);
    vsnprintf(buf, sizeof(buf) - 1, fmt, arguments);
    va_end(arguments);
    debug_string(buf);
}

