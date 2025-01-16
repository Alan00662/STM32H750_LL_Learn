
#include "driver_haptic.h"
#include "tim.h"

void hapticInit(void)
{
	MX_TIM3_Init();
}

void hapticOn(uint32_t pwmPercent)
{
  if (pwmPercent > 100) pwmPercent = 100;
		LL_TIM_OC_SetCompareCH2(TIM2, pwmPercent);
//  stm32_pulse_set_cmp_val(&_haptic_timer, pwmPercent);
}

void hapticOff(void) { hapticOn(0); }
void hapticDone(void) { hapticOff(); }