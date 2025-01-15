
#include "driver_pwr.h"
#include "gpio.h"
#include "hal.h"
void pwrInit(void) 
{ 
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOH);
	
	  /**/
  LL_GPIO_ResetOutputPin(PWR_ON_GPIO, PWR_ON_GPIO_PIN);
	
  /**/
  GPIO_InitStruct.Pin = PWR_ON_GPIO_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWR_ON_GPIO, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWR_SWITCH_GPIO_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWR_SWITCH_GPIO, &GPIO_InitStruct);
	
}


_Bool pwrPressed(void)
{
  return !LL_GPIO_IsOutputPinSet(PWR_SWITCH_GPIO,PWR_SWITCH_GPIO_PIN);

}

_Bool pwrOffPressed(void)
{
	return !pwrPressed();
}
