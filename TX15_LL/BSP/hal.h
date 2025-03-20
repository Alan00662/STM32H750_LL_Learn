#ifndef __HAL_H__
#define __HAL_H__

#include "main.h"

#define CPU_FREQ                480000000

#define PERI1_FREQUENCY         120000000
#define PERI2_FREQUENCY         120000000
#define TIMER_MULT_APB1         2
#define TIMER_MULT_APB2         2

// Keys
#define KEYS_GPIO_REG_PAGEDN          GPIOA
#define KEYS_GPIO_PIN_PAGEDN          LL_GPIO_PIN_8  // PA.08
#define KEYS_GPIO_REG_PAGEUP          GPIOG
#define KEYS_GPIO_PIN_PAGEUP          LL_GPIO_PIN_7  // PG.07
#define KEYS_GPIO_REG_SYS             GPIOB
#define KEYS_GPIO_PIN_SYS             LL_GPIO_PIN_2  // PB.02
#define KEYS_GPIO_REG_ENTER           GPIOG
#define KEYS_GPIO_PIN_ENTER           LL_GPIO_PIN_12 // PG.12
#define KEYS_GPIO_REG_MDL             GPIOE
#define KEYS_GPIO_PIN_MDL             LL_GPIO_PIN_3  // PE.03
#define KEYS_GPIO_REG_EXIT            GPIOG
#define KEYS_GPIO_PIN_EXIT            LL_GPIO_PIN_3  // PG.03
#define KEYS_GPIO_REG_TELE            GPIOG
#define KEYS_GPIO_PIN_TELE            LL_GPIO_PIN_2  // PG.02
// Trims

// function switches
#define FUNCTION_SWITCH_1               I2C
#define FUNCTION_SWITCH_2               I2C
#define FUNCTION_SWITCH_3               I2C
#define FUNCTION_SWITCH_4               I2C
#define FUNCTION_SWITCH_5               I2C
#define FUNCTION_SWITCH_6               I2C

// Extender Switches
#define SWITCHES_A_3POS
#define SWITCHES_B_3POS
#define SWITCHES_C_3POS
#define SWITCHES_D_3POS
#define SWITCHES_E_3POS
#define SWITCHES_F_3POS

// Expanders
#define IO_INT_GPIO 									GPIOD
#define IO_INT_GPIO_PIN								LL_GPIO_PIN_3
#define IO_RESET_GPIO									GPIOG 
#define IO_RESET_GPIO_PIN 						LL_GPIO_PIN_10

#define USE_EXTI3_IRQ
#define EXTI3_IRQ_Priority  9

// ADC
#define ADC_GPIO_PIN_STICK_LH           LL_GPIO_PIN_6      // PA.06
#define ADC_GPIO_PIN_STICK_LV           LL_GPIO_PIN_3      // PC.03
#define ADC_GPIO_PIN_STICK_RV           LL_GPIO_PIN_4      // PC.04
#define ADC_GPIO_PIN_STICK_RH           LL_GPIO_PIN_5      // PC.05

#define ADC_GPIO_PIN_POT1               LL_GPIO_PIN_1      // PC.01 POT1
#define ADC_GPIO_PIN_POT2               LL_GPIO_PIN_1      // PB.01 POT2
#define ADC_GPIO_PIN_BATT               LL_GPIO_PIN_3      // PH.03

#define ADC_GPIOA_PINS                  (ADC_GPIO_PIN_STICK_LH )
#define ADC_GPIOB_PINS                  (ADC_GPIO_PIN_POT2)
#define ADC_GPIOC_PINS                  (ADC_GPIO_PIN_STICK_RV | ADC_GPIO_PIN_STICK_LV|ADC_GPIO_PIN_STICK_RH | ADC_GPIO_PIN_POT1)
#define ADC_GPIOH_PINS                  (ADC_GPIO_PIN_BATT)


#define ADC_CHANNEL_STICK_LH            LL_ADC_CHANNEL_3    // ADC12_INP3
#define ADC_CHANNEL_STICK_LV            LL_ADC_CHANNEL_1    // ADC12_INP1
#define ADC_CHANNEL_STICK_RV            LL_ADC_CHANNEL_4    // ADC12_INP4
#define ADC_CHANNEL_STICK_RH            LL_ADC_CHANNEL_8    // ADC12_INP8

// Each ADC cannot map more than 8 channels, otherwise it will cause problems
#define ADC_CHANNEL_POT1                LL_ADC_CHANNEL_11   // ADC12_INP11
#define ADC_CHANNEL_POT2                LL_ADC_CHANNEL_5    // ADC12_INP5
#define ADC_CHANNEL_BATT                LL_ADC_CHANNEL_14   // ADC123_INP14
#define ADC_CHANNEL_RTC_BAT             LL_ADC_CHANNEL_VBAT // ADC12_IN14

#define ADC_MAIN                        ADC1
#define ADC_DMA                         DMA2
#define ADC_DMA_CHANNEL                 LL_DMAMUX1_REQ_ADC1
#define ADC_DMA_STREAM                  LL_DMA_STREAM_4
#define ADC_DMA_STREAM_IRQ              DMA2_Stream4_IRQn
#define ADC_DMA_STREAM_IRQHandler       DMA2_Stream4_IRQHandler
#define ADC_SAMPTIME                    LL_ADC_SAMPLINGTIME_64CYCLES_5

#define ADC_EXT_DMA                     DMA2
#define ADC_EXT_DMA_CHANNEL             LL_DMAMUX1_REQ_ADC3
#define ADC_EXT_DMA_STREAM              LL_DMA_STREAM_0
#define ADC_EXT_DMA_STREAM_IRQ          DMA2_Stream0_IRQn
#define ADC_EXT_DMA_STREAM_IRQHandler   DMA2_Stream0_IRQHandler
#define ADC_EXT_SAMPTIME                LL_ADC_SAMPLINGTIME_64CYCLES_5

#define ADC_VREF_PREC2                  330

// Haptic: TIM3_CH2
#define HAPTIC_PWM
#define HAPTIC_GPIO                     GPIO_PIN(GPIOC, 7)
#define HAPTIC_GPIO_TIMER               TIM3
#define HAPTIC_GPIO_AF                  GPIO_AF2
#define HAPTIC_TIMER_OUTPUT_ENABLE      TIM_CCER_CC2E | TIM_CCER_CC2NE;
#define HAPTIC_TIMER_MODE               TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE
#define HAPTIC_TIMER_COMPARE_VALUE      HAPTIC_GPIO_TIMER->CCR2

// Flysky Hall Stick
#define FLYSKY_HALL_SERIAL_USART                 UART4

#define FLYSKY_HALL_SERIAL_TX_GPIO               GPIO_PIN(GPIOB, 9)
#define FLYSKY_HALL_SERIAL_RX_GPIO               GPIO_PIN(GPIOB, 8)
#define FLYSKY_HALL_SERIAL_USART_IRQn            UART4_IRQn

#define FLYSKY_HALL_SERIAL_DMA                   DMA1
#define FLYSKY_HALL_DMA_Stream_RX                LL_DMA_STREAM_2
#define FLYSKY_HALL_DMA_Channel                  LL_DMAMUX1_REQ_UART4_RX

// LED Strip
#define LED_STRIP_LENGTH                  6
#define LED_STRIP_GPIO                    GPIOA
#define LED_STRIP_GPIO_PIN                LL_GPIO_PIN_0 // PA.00 / TIM2_CH1
#define LED_STRIP_GPIO_AF                 LL_GPIO_AF_1         // TIM1/2/16/17
#define LED_STRIP_TIMER                   TIM2
#define LED_STRIP_TIMER_FREQ              (PERI1_FREQUENCY * TIMER_MULT_APB1)
#define LED_STRIP_TIMER_CHANNEL           LL_TIM_CHANNEL_CH1
#define LED_STRIP_TIMER_DMA               DMA1
#define LED_STRIP_TIMER_DMA_CHANNEL       LL_DMAMUX1_REQ_TIM2_UP
#define LED_STRIP_TIMER_DMA_STREAM        LL_DMA_STREAM_0
#define LED_STRIP_TIMER_DMA_IRQn          DMA1_Stream0_IRQn
#define LED_STRIP_TIMER_DMA_IRQHandler    DMA1_Stream0_IRQHandler
#define LED_STRIP_REFRESH_PERIOD          50 //ms

#define STATUS_LEDS
#define GPIO_LED_GPIO_ON                  LL_GPIO_SetOutputPin
#define GPIO_LED_GPIO_OFF                 LL_GPIO_ResetOutputPin
#define LED_RED_GPIO_PIN 									LL_GPIO_PIN_8
#define LED_RED_GPIO 											GPIOI
#define LED_BLUE_GPIO_PIN 								LL_GPIO_PIN_10
#define LED_BLUE_GPIO 										GPIOI
#define LED_GREEN_GPIO_PIN 								LL_GPIO_PIN_11
#define LED_GREEN_GPIO 										GPIOI

// Power
#define PWR_SWITCH_GPIO            			GPIOA
#define PWR_SWITCH_GPIO_PIN             LL_GPIO_PIN_4
#define PWR_ON_GPIO                     GPIOH
#define PWR_ON_GPIO_PIN                 LL_GPIO_PIN_12

// LCD
#define LCD_SPI_CS_GPIO                 GPIOA
#define LCD_SPI_CS_GPIO_PIN             LL_GPIO_PIN_7
#define LCD_SPI_SCK_GPIO                GPIOB
#define LCD_SPI_SCK_GPIO_PIN            LL_GPIO_PIN_0
#define LCD_SPI_MOSI_GPIO               GPIOI
#define LCD_SPI_MOSI_GPIO_PIN           LL_GPIO_PIN_9
#define LTDC_IRQ_PRIO                   4
#define DMA_SCREEN_IRQ_PRIO             6

#define LCD_RESET_GPIO                  GPIOJ
#define LCD_RESET_GPIO_PIN              LL_GPIO_PIN_12

// Backlight
#define BACKLIGHT_GPIO                  GPIOA
#define BACKLIGHT_GPIO_PIN              LL_GPIO_PIN_10
#define BACKLIGHT_TIMER                 TIM8
#define BACKLIGHT_GPIO_AF               GPIO_AF3
#define BACKLIGHT_TIMER_FREQ            (PERI1_FREQUENCY * TIMER_MULT_APB1)

// USB
#define USB_GPIO                        GPIOA
#define USB_GPIO_VBUS                   GPIOH
#define USB_GPIO_VBUS_PIN               LL_GPIO_PIN_5
#define USB_GPIO_DM                     GPIOA
#define USB_GPIO_DM_PIN                 LL_GPIO_PIN_11
#define USB_GPIO_DP                     GPIOA
#define USB_GPIO_DP_PIN                 LL_GPIO_PIN_12
#define USB_GPIO_AF                     GPIO_AF10

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


