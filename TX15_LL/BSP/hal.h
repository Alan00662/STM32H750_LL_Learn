#ifndef __HAL_H__
#define __HAL_H__

#include "main.h"
// LCD
#define LCD_SPI_CS_GPIO                 GPIOG
#define LCD_SPI_CS_GPIO_PIN             LL_GPIO_PIN_6
#define LCD_SPI_GPIO                    GPIOF
#define LCD_SPI_SCK_GPIO_PIN            LL_GPIO_PIN_10
#define LCD_SPI_MOSI_GPIO_PIN           LL_GPIO_PIN_8
#define LTDC_IRQ_PRIO                   4
#define DMA_SCREEN_IRQ_PRIO             6

#define LCD_RESET_GPIO                  GPIOJ
#define LCD_RESET_GPIO_PIN              LL_GPIO_PIN_12

// Backlight
#define BACKLIGHT_GPIO                  GPIO_PIN(GPIOI, 2) // TIM8_CH4
#define BACKLIGHT_TIMER                 TIM8
#define BACKLIGHT_GPIO_AF               GPIO_AF3
#define BACKLIGHT_TIMER_FREQ            (PERI1_FREQUENCY * TIMER_MULT_APB1)


//ROTARY emulation for trims as buttons
#define ROTARY_ENCODER_NAVIGATION
// Rotary Encoder
#define ROTARY_ENCODER_INVERTED
#define ROTARY_ENCODER_GPIO_A           GPIOI
#define ROTARY_ENCODER_GPIO_PIN_A       LL_GPIO_PIN_7
#define ROTARY_ENCODER_GPIO_B           GPIOJ
#define ROTARY_ENCODER_GPIO_PIN_B       LL_GPIO_PIN_8
#define ROTARY_ENCODER_POSITION()       (((ROTARY_ENCODER_GPIO_A->IDR >> 7) & 0x01)|((ROTARY_ENCODER_GPIO_B->IDR >> 7) & 0x02))
#define ROTARY_ENCODER_EXTI_LINE1       LL_EXTI_LINE_7
#define ROTARY_ENCODER_EXTI_LINE2       LL_EXTI_LINE_8

#define EXTI7_IRQ_Priority 5
#define EXTI8_IRQ_Priority 5

#define ROTARY_ENCODER_EXTI_PORT_A      LL_SYSCFG_EXTI_PORTI
#define ROTARY_ENCODER_EXTI_PORT_B      LL_SYSCFG_EXTI_PORTJ
#define ROTARY_ENCODER_EXTI_SYS_LINE1   LL_SYSCFG_EXTI_LINE7
#define ROTARY_ENCODER_EXTI_SYS_LINE2   LL_SYSCFG_EXTI_LINE8
#define ROTARY_ENCODER_TIMER            TIM17
#define ROTARY_ENCODER_TIMER_IRQn       TIM17_IRQn
#define ROTARY_ENCODER_TIMER_IRQHandler TIM17_IRQHandler


#define LANDSCAPE_LCD true
#define PORTRAIT_LCD false

#define LCD_W                           480
#define LCD_H                           320

#define LCD_PHYS_W                      LCD_H
#define LCD_PHYS_H                      LCD_W

#define LCD_DEPTH                       16


#endif


