#ifndef _DRIVER_POWER_H
#define _DRIVER_POWER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
#include "hal.h"
enum {
  PWR_OFF = 0,
  PWR_ON,
  PWR_NONE
};

#define POWER_ON()  do{HAL_GPIO_WritePin(PWR_EN_GPIO_Port,PWR_EN_Pin,GPIO_PIN_SET);} while(0)
#define POWER_OFF()   do{HAL_GPIO_WritePin(PWR_EN_GPIO_Port,PWR_EN_Pin,GPIO_PIN_RESET);} while(0)
#define INRF_PWR_EN()  do{HAL_GPIO_WritePin(PWR_INRF_GPIO_Port,PWR_INRF_Pin,GPIO_PIN_SET);} while(0)
#define INRF_PWR_OFF()   do{HAL_GPIO_WritePin(PWR_INRF_GPIO_Port,PWR_INRF_Pin,GPIO_PIN_RESET);} while(0)
#define EXTRF_PWR_EN()  do{HAL_GPIO_WritePin(PWR_EXTRF_GPIO_Port,PWR_EXTRF_Pin,GPIO_PIN_SET);} while(0)
#define EXTRF_PWR_OFF()   do{HAL_GPIO_WritePin(PWR_EXTRF_GPIO_Port,PWR_EXTRF_Pin,GPIO_PIN_RESET);} while(0)

#define POWER_SWITCH_PRESSED()  (HAL_GPIO_ReadPin(PWR_SW_GPIO_Port,PWR_SW_Pin)==0)?1:0


void power_init(void);

#ifdef __cplusplus
}
#endif

#endif