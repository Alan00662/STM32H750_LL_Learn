#ifndef __BOARD_H__
#define __BOARD_H__

#include "main.h"

#include "hal.h"
#include "driver_extflash.h"
#include "driver_lcd.h"
#include "driver_key.h"
#include "driver_pwr.h"
#include "driver_backlight.h"
#include "driver_haptic.h"
#include "driver_led.h"

// Backlight driver
#define BACKLIGHT_LEVEL_MAX             100
#define BACKLIGHT_FORCED_ON             BACKLIGHT_LEVEL_MAX + 1
#define BACKLIGHT_LEVEL_MIN             1

void boardInit(void);
#endif


