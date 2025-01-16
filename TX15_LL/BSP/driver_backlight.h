#ifndef __DRIVER_BACKLIGHT_H__
#define __DRIVER_BACKLIGHT_H__

#include "main.h"

void backlightEnable(uint8_t dutyCycle);

#define lcdOff()              backlightEnable(0) /* just disable the backlight */
void lcdOn(void);
_Bool isBacklightEnabled(void);
#endif

