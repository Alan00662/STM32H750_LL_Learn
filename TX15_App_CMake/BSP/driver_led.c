

#include "driver_led.h"
#include "hal.h"

void led_init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = LEDG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LEDG_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LEDR_Pin;
  HAL_GPIO_Init(LEDR_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = LEDB_Pin;
  HAL_GPIO_Init(LEDB_GPIO_Port, &GPIO_InitStruct);

  LED_BLUE_OFF();
  LED_RED_OFF();

  LED_GREEN_OFF();
}

