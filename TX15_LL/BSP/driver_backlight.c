#include "board.h"
#include "driver_backlight.h"

void backlightEnable(uint8_t dutyCycle)
{
	  if (dutyCycle > 100) dutyCycle = 100;
		LL_TIM_OC_SetCompareCH4(TIM8, dutyCycle);
}

void lcdOn(void)
{
  // if(lcdOnFunction) lcdOnFunction();
  // else lcdInit();
  backlightEnable(BACKLIGHT_LEVEL_MAX);
}

_Bool boardBacklightOn;

_Bool isBacklightEnabled(void)
{
  return boardBacklightOn;
}