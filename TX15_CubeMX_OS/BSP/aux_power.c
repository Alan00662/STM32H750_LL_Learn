
#include "aux_power.h"


void AUX_Power_Init(void)    
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable *

  /* GPIO Ports Clock Enable */
  AUX1_PWR_GPIO_CLK_ENABLE();
  AUX2_PWR_GPIO_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(AUX1_PWER_GPIO_PORT, AUX1_PWR_GPIO_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AUX2_PWR_GPIO_PORT, AUX2_PWR_GPIO_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pins : PIPin PIPin PIPin */
  GPIO_InitStruct.Pin = AUX1_PWR_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AUX1_PWER_GPIO_PORT, &GPIO_InitStruct);

    /*Configure GPIO pins : PIPin PIPin PIPin */
  GPIO_InitStruct.Pin = AUX2_PWR_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AUX2_PWR_GPIO_PORT, &GPIO_InitStruct);

  AUX1_PWR_Set(1);
  AUX2_PWR_Set(1);
}

