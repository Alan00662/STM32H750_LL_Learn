#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "gpio.h"
#include "debug.h"
#include "i2c.h"
#include "ltdc.h"
#include "dma2d.h"
#include "tim.h"

#include "hal.h"
#include "driver_led.h"
#include "driver_power.h"
#include "driver_gt911.h"
#include "driver_lcd.h"
#include "system_clock.h"

#include "app.h"
void board_init(void);



#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

