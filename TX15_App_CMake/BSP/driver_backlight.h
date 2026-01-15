#ifndef _DRIVER_BACKLIGHT_H
#define _DRIVER_BACKLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

void backlight_init(void);
void backlight_pwm(uint8_t pwm);
#ifdef __cplusplus
}
#endif

#endif