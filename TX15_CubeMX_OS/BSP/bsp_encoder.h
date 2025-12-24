#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "main.h"

#define ROTENC_OUT		0

#define ROTENC_A_GPIO_PORT            GPIOI
#define ROTENC_A_GPIO_PIN             GPIO_PIN_7
#define ROTENC_A_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

#define ROTENC_B_GPIO_PORT            GPIOJ
#define ROTENC_B_GPIO_PIN             GPIO_PIN_8
#define ROTENC_B_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)


#define ROTENC_A  HAL_GPIO_ReadPin(ROTENC_A_GPIO_PORT, ROTENC_A_GPIO_PIN)
#define ROTENC_B  HAL_GPIO_ReadPin(ROTENC_B_GPIO_PORT, ROTENC_B_GPIO_PIN)

#define ROTENC_B_Out(x)               do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(ROTENC_B_GPIO_PORT, ROTENC_B_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(ROTENC_B_GPIO_PORT, ROTENC_B_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)


extern int32_t Encoder;
void Encoder_Init(void);

#endif /* __MOTOR_H__ */

