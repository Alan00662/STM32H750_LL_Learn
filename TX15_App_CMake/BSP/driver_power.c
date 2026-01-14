#include "driver_power.h"
#include "hal.h"

void power_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = PWR_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(PWR_EN_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = PWR_INRF_Pin;
  HAL_GPIO_Init(PWR_INRF_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = PWR_EXTRF_Pin;
  HAL_GPIO_Init(PWR_EXTRF_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = PWR_SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PWR_SW_GPIO_Port, &GPIO_InitStruct);

}
