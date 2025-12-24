
#include "rf_power.h"

void RF_Power_Init(void)    
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};


  /* GPIO Ports Clock Enable */
  EXRF_GPIO_CLK_ENABLE();
  INRF_GPIO_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EXRF_GPIO_PORT, EXRF_GPIO_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(INRF_GPIO_PORT, INRF_GPIO_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pins : PIPin PIPin PIPin */
  GPIO_InitStruct.Pin = EXRF_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EXRF_GPIO_PORT, &GPIO_InitStruct);

    /*Configure GPIO pins : PIPin PIPin PIPin */
  GPIO_InitStruct.Pin = INRF_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(INRF_GPIO_PORT, &GPIO_InitStruct);

  EXRF_Set(1);
  INRF_Set(1);
}

