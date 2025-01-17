#ifndef __DRIVER_BATTERY_H__
#define __DRIVER_BATTERY_H__

#include "main.h"

#define BATTERY_WARN                  74 // 7.4V
#define BATTERY_MIN                   70 // 6.8V
#define BATTERY_MAX                   86 // 8.6V
#define BATTERY_DIVIDER               2323

void adcInit(void);
#endif

