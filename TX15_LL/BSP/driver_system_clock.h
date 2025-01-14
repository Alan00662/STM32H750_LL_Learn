#ifndef __DRIVER_SYSTEM_CLOCK_H__
#define __DRIVER_SYSTEM_CLOCK_H__

#include "main.h"

uint32_t millis(void);
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
void MPU_Config(void);
void Error_Handler(void);
#endif 

