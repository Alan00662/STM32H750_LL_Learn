#ifndef __DRIVER_BACKLIGHT_H__
#define __DRIVER_BACKLIGHT_H__

#include "main.h"
#define BackLight_USE_PWM 	0
void backlightEnable(uint8_t dutyCycle);

#define lcdOff()              backlightEnable(0) /* just disable the backlight */
void lcdOn(void);
_Bool isBacklightEnabled(void);

void backlight_gpio_init(void);

#endif

