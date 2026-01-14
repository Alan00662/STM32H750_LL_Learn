#ifndef _DRIVER_LED_H
#define _DRIVER_LED_H

#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
#define LED_GREEN_OFF()  do{HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_RESET);} while(0)
#define LED_GREEN_ON()   do{HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_SET);} while(0)
#define LED_GREEN_Toggle()   do{HAL_GPIO_TogglePin(LEDG_GPIO_Port,LEDG_Pin);} while(0)

#define LED_BLUE_OFF()  do{HAL_GPIO_WritePin(LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_RESET);} while(0)
#define LED_BLUE_ON()   do{HAL_GPIO_WritePin(LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_SET);} while(0)
#define LED_BLUE_Toggle()   do{HAL_GPIO_TogglePin(LEDB_GPIO_Port,LEDB_Pin);} while(0)

#define LED_RED_OFF()  do{HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,GPIO_PIN_RESET);} while(0)
#define LED_RED_ON()   do{HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,GPIO_PIN_SET);} while(0)
#define LED_RED_Toggle()   do{HAL_GPIO_TogglePin(LEDR_GPIO_Port,LEDR_Pin);} while(0)

void led_init(void);

#ifdef __cplusplus
}
#endif

#endif