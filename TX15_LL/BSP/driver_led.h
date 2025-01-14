#ifndef __DRIVER_LED_H__
#define __DRIVER_LED_H__

#include "main.h"

#define LED0(x)                   do { (x) ?                                                                  \
                                        LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin):     \
                                        LL_GPIO_ResetOutputPin(LED0_GPIO_Port, LED0_Pin);   \
                                    } while (0)
#define LED1(x)                   do { (x) ?                                                                  \
                                        LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin):     \
                                        LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);   \
                                    } while (0)
#define LED2(x)                   do { (x) ?                                                                  \
                                        LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin):     \
                                        LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);   \
                                    } while (0)

void led0_bink(uint16_t ms);
void led1_bink(uint16_t ms);
void led2_bink(uint16_t ms);
void led_Loop_bink(uint16_t ms);

#endif /* __BSP_LED_H__ */

