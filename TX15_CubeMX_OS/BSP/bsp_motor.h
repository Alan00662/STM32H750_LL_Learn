#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"
//HAPTIC
#define MOTOR_GPIO_PORT            GPIOC
#define MOTOR_GPIO_PIN             GPIO_PIN_7
#define MOTOR_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)

#define Motor_Set(x)                do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

void Motor_Init(void);
void Motor_pwm(uint16_t pwm);
#endif /* __MOTOR_H__ */

