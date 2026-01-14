#ifndef __SYSTEM_CLOCK_H__
#define __SYSTEM_CLOCK_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void SystemClock_Config(void);
void MPU_Config(void);
void PeriphCommonClock_Config(void);
#ifdef __cplusplus
}
#endif
#endif //__TCA9539_H__
