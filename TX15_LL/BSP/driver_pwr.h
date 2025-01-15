#ifndef __DRIVER_PWR_H__
#define __DRIVER_PWR_H__

#include "main.h"
#include "gpio.h"
#include "hal.h"
void pwrInit(void); 

#define		pwrOn() 		LL_GPIO_SetOutputPin(PWR_ON_GPIO, PWR_ON_GPIO_PIN)
#define		pwrOff() 		LL_GPIO_ResetOutputPin(PWR_ON_GPIO, PWR_ON_GPIO_PIN)

_Bool pwrPressed(void);
_Bool pwrOffPressed(void);

#endif

