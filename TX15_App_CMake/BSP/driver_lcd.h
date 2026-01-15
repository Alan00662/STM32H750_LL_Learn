#ifndef __LCD_H
#define __LCD_H

#include "main.h"

#define TFT_BL_GPIO_PORT            GPIOA
#define TFT_BL_GPIO_PIN             GPIO_PIN_10
#define TFT_BL_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)

#define TFT_CLK_GPIO_PORT            GPIOB
#define TFT_CLK_GPIO_PIN             GPIO_PIN_0
#define TFT_CLK_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)

#define TFT_MOSI_GPIO_PORT            GPIOI
#define TFT_MOSI_GPIO_PIN             GPIO_PIN_9
#define TFT_MOSI_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

#define TFT_CS_GPIO_PORT            GPIOA
#define TFT_CS_GPIO_PIN             GPIO_PIN_7
#define TFT_CS_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)

#define TFT_RESET_GPIO_PORT            GPIOJ
#define TFT_RESET_GPIO_PIN             GPIO_PIN_12
#define TFT_RESET_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)

#define TFT_BL(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)


#define TFT_CLK(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);   \
                                    } while (0)

#define TFT_MOSI(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(GPIOI, GPIO_PIN_9, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(GPIOI, GPIO_PIN_9, GPIO_PIN_RESET);   \
                                    } while (0)


#define TFT_CS(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_CS_GPIO_PORT, TFT_CS_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_CS_GPIO_PORT, TFT_CS_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)


#define TFT_RST(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_RESET_GPIO_PORT, TFT_RESET_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_RESET_GPIO_PORT, TFT_RESET_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

void st7796_init(void);

#endif
