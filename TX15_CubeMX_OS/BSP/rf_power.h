#ifndef __RF_POWER_H__
#define __RF_POWER_H__

#include "main.h"

#define EXRF_GPIO_PORT            GPIOD
#define EXRF_GPIO_PIN             GPIO_PIN_14
#define EXRF_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOD_CLK_ENABLE(); } while (0)

#define INRF_GPIO_PORT            GPIOB
#define INRF_GPIO_PIN             GPIO_PIN_13
#define INRF_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)


#define EXRF_Set(x)                do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(EXRF_GPIO_PORT, EXRF_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(EXRF_GPIO_PORT, EXRF_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

#define INRF_Set(x)                do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(INRF_GPIO_PORT, INRF_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(INRF_GPIO_PORT, INRF_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

void RF_Power_Init(void);

#endif /* __MOTOR_H__ */

