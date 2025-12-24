#ifndef __AUX_POWER_H__
#define __AUX_POWER_H__

#include "main.h"

#define AUX1_PWER_GPIO_PORT            GPIOB
#define AUX1_PWR_GPIO_PIN             GPIO_PIN_7
#define AUX1_PWR_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)

#define AUX2_PWR_GPIO_PORT            GPIOC
#define AUX2_PWR_GPIO_PIN             GPIO_PIN_3
#define AUX2_PWR_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)


#define AUX1_PWR_Set(x)                do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(AUX1_PWER_GPIO_PORT, AUX1_PWR_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(AUX1_PWER_GPIO_PORT, AUX1_PWR_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

#define AUX2_PWR_Set(x)                do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(AUX2_PWR_GPIO_PORT, AUX2_PWR_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(AUX2_PWR_GPIO_PORT, AUX2_PWR_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

void AUX_Power_Init(void);

#endif /* __MOTOR_H__ */

