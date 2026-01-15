
#include "main.h"
#include "board.h"
TIM_HandleTypeDef tim_backlight;

void backlight_init(void)
{

#ifdef BACKLIGHT_USE_PWM
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = BACKLIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = BACKLIGHT_AF;
  HAL_GPIO_Init(BACKLIGHT_GPIO_Port, &GPIO_InitStruct);
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  BACKLIGHT_TIM_CLK();
  tim_backlight.Instance = BACKLIGHT_TIM;
  tim_backlight.Init.Prescaler = TIM_1MHz_PSC-1;
  tim_backlight.Init.CounterMode = TIM_COUNTERMODE_UP;
  tim_backlight.Init.Period = 100-1;
  tim_backlight.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  tim_backlight.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&tim_backlight) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&tim_backlight, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&tim_backlight, &sConfigOC, BACKLIGHT_CH) != HAL_OK)
  {
    Error_Handler();
  }
#else
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = BACKLIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BACKLIGHT_GPIO_Port, &GPIO_InitStruct);
#endif
}
void backlight_pwm(uint8_t pwm)
{
#ifdef BACKLIGHT_USE_PWM
	HAL_TIM_PWM_Start(&tim_backlight, BACKLIGHT_CH);
  __HAL_TIM_SET_COMPARE(&tim_backlight, BACKLIGHT_CH, pwm);
#else
  if(pwm>0)
    HAL_GPIO_WritePin(BACKLIGHT_GPIO_Port, BACKLIGHT_Pin, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(BACKLIGHT_GPIO_Port, BACKLIGHT_Pin, GPIO_PIN_RESET);
#endif
}
