#include "board.h"
#include "driver_backlight.h"

void backlightEnable(uint8_t dutyCycle)
{
	  if (dutyCycle > 100) dutyCycle = 100;

		LL_TIM_OC_SetCompareCH4(TIM8, dutyCycle*100);
}

void lcdOn(void)
{
#if BackLight_USE_PWM == 1
	  // if(lcdOnFunction) lcdOnFunction();
  // else lcdInit();
  backlightEnable(BACKLIGHT_LEVEL_MAX);

		#else
		LL_GPIO_SetOutputPin(BACKLIGHT_GPIO, BACKLIGHT_GPIO_PIN);
	#endif
}

_Bool boardBacklightOn;

_Bool isBacklightEnabled(void)
{
  return boardBacklightOn;
}

void backlight_gpio_init(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStructure;
  LL_GPIO_StructInit(&GPIO_InitStructure);

  GPIO_InitStructure.Pin        =  BACKLIGHT_GPIO_PIN;
  GPIO_InitStructure.Speed      = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStructure.Mode       = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStructure.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BACKLIGHT_GPIO, &GPIO_InitStructure);
}
