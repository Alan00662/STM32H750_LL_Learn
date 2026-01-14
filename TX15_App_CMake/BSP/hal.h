#ifndef _HAL_H
#define _HAL_H
#include "main.h"



#define _PRODUCTNAME "TX15"
#define _SKETCHVERSION "1.0.0"
// #define HSE_VALUE    12000000U
// ADC
#define ADC_USE_DMA


#define ADC_RV_Pin              GPIO_PIN_4
#define ADC_RV_GPIO_Port        GPIOC
#define ADC_LV_Pin              GPIO_PIN_0_C
#define ADC_LV_GPIO_Port        GPIOA
#define ADC_LH_Pin              GPIO_PIN_6
#define ADC_LH_GPIO_Port        GPIOA
#define ADC_RH_Pin              GPIO_PIN_5
#define ADC_RH_GPIO_Port        GPIOC
#define ADC_S2_Pin              GPIO_PIN_1
#define ADC_S2_GPIO_Port        GPIOB
#define ADC_S1_Pin              GPIO_PIN_1
#define ADC_S1_GPIO_Port        GPIOC
#define BAT_Pin                 GPIO_PIN_3
#define BAT_GPIO_Port           GPIOH
#define ADC_CH_RV               ADC_CHANNEL_0
#define ADC_CH_RH               ADC_CHANNEL_1
#define ADC_CH_LV               ADC_CHANNEL_14
#define ADC_CH_LH               ADC_CHANNEL_15
#define ADC_CH_S2               ADC_CHANNEL_5
#define ADC_CH_S1               ADC_CHANNEL_11
#define ADC_CH_BAT              ADC_CHANNEL_14
#define ADC_DMA_CH              DMA1_Channel0
#define ADC_DMA_IRQ             DMA1_Channel0_IRQn
#define ADC_DMA_IRQHandler      DMA1_Channel0_IRQHandler
// KEY

#define KEY_ENTER_Pin           GPIO_PIN_12  
#define KEY_ENTER_GPIO_Port     GPIOG
#define KEY_RTN_Pin           GPIO_PIN_3
#define KEY_RTN_GPIO_Port     GPIOG
#define KEY_TELE_Pin           GPIO_PIN_2
#define KEY_TELE_GPIO_Port     GPIOG
#define KEY_SYS_Pin           GPIO_PIN_2
#define KEY_SYS_GPIO_Port     GPIOB
#define KEY_MDL_Pin           GPIO_PIN_3
#define KEY_MDL_GPIO_Port     GPIOE
#define KEY_PAGE_L_Pin           GPIO_PIN_7
#define KEY_PAGE_L_GPIO_Port     GPIOG
#define KEY_PAGE_R_Pin           GPIO_PIN_8
#define KEY_PAGE_R_GPIO_Port     GPIOA

//Trims


//Switch
#define IO_EXPANDER_I2C 
#define SWITCH_RES_GPIO_PORT          GPIOJ
#define SWITCH_RES_GPIO_PIN           GPIO_PIN_4
#define TCA9539_INT_GPIO_PORT           GPIOD
#define TCA9539_INT_GPIO_PIN            GPIO_PIN_3



// #define SWITCH_E_L	IO_BIT6
// #define SWITCH_E_H	IO_BIT7
// #define SWITCH_D_L	IO_BIT0
// #define SWITCH_D_H	IO_BIT1
// #define SWITCH_C_L	IO_BIT2
// #define SWITCH_C_H	IO_BIT3
// #define SWITCH_B_L	IO_BIT4
// #define SWITCH_B_H	IO_BIT5
// #define SWITCH_A_L	IO_BIT6
// #define SWITCH_A_H	IO_BIT7

// #define K1	IO_BIT0
// #define K2	IO_BIT1
// #define K3	IO_BIT2
// #define K4	IO_BIT3
// #define K5	IO_BIT4
// #define K6	IO_BIT5

// Rotenc
// #define ROTARY_ENCODER_NAVIGATION
#define ROTARY_A_GPIO_PORT            GPIOJ
#define ROTARY_A_GPIO_PIN             GPIO_PIN_7
#define ROTARY_B_GPIO_PORT            GPIOJ
#define ROTARY_B_GPIO_PIN             GPIO_PIN_8
#define ROTARY_IRQ                    EXTI9_5_IRQn
#define ROTARY_IRQHandler             EXTI9_5_IRQHandler
#define ROTARY_IRQ_Priority           3
// LED

#define LEDG_Pin GPIO_PIN_11
#define LEDG_GPIO_Port GPIOI
#define LEDB_Pin GPIO_PIN_10
#define LEDB_GPIO_Port GPIOI
#define LEDR_Pin GPIO_PIN_8
#define LEDR_GPIO_Port GPIOI
//LCD
#define LCD_CS_Pin              GPIO_PIN_7
#define LCD_CS_GPIO_Port        GPIOA
#define LCD_RST_Pin             GPIO_PIN_12
#define LCD_RST_GPIO_Port       GPIOJ
#define LCD_CLK_Pin             GPIO_PIN_0
#define LCD_CLK_GPIO_Port       GPIOB
#define LCD_MOSI_Pin            GPIO_PIN_9
#define LCD_MOSI_GPIO_Port      GPIOI

#define LCDWIDTH                480
#define LCDHEIGHT               320
// backlight
#define BACKLIGHT_USE_PWM
#define BACKLIGHT_Pin GPIO_PIN_10
#define BACKLIGHT_GPIO_Port GPIOA
#define BACKLIGHT_AF  GPIO_AF1_TIM1
#define BACKLIGHT_TIM   TIM1
#define BACKLIGHT_CH TIM_CHANNEL_3
//haptic
#define HAPTIC_Pin GPIO_PIN_7
#define HAPTIC_GPIO_Port GPIOC
#define HAPTIC_AF  GPIO_AF2_TIM3
#define HAPTIC_TIM   TIM3
#define HAPTIC_CH TIM_CHANNEL_2
//Power
#define PWR_EN_Pin GPIO_PIN_12
#define PWR_EN_GPIO_Port GPIOH
#define PWR_SW_Pin GPIO_PIN_4
#define PWR_SW_GPIO_Port GPIOA
// In RF
#define PWR_INRF_Pin GPIO_PIN_3
#define PWR_INRF_GPIO_Port GPIOB
#define INRF_TX_Pin GPIO_PIN_3
#define INRF_TX_GPIO_Port GPIOB
#define INRF_TX_AF 
#define INRF_RX_Pin GPIO_PIN_3
#define INRF_RX_GPIO_Port GPIOB
#define INRF_RX_AF 
#define INRF_BOOT_Pin GPIO_PIN_9
#define INRF_BOOT_GPIO_Port GPIOH
// Ext RF
#define PWR_EXTRF_Pin GPIO_PIN_4
#define PWR_EXTRF_GPIO_Port GPIOD
#define EXTRF_TX_Pin GPIO_PIN_3
#define EXTRF_TX_GPIO_Port GPIOB
#define EXTRF_TX_AF 
#define EXTRF_RX_Pin GPIO_PIN_3
#define EXTRF_RX_GPIO_Port GPIOB
#define EXTRF_RX_AF 
// Sport
#define SPORT_TX_Pin GPIO_PIN_9
#define SPORT_TX_GPIO_Port GPIOA
//EEPROM

//RGB
#define RGB_LED_Pin             GPIO_PIN_0
#define RGB_LED_GPIO_Port       GPIOA
#define RGB_AF                  GPIO_AF1_TIM1
#define RGB_TIM                 TIM1
#define RGB_CH                  TIM_CHANNEL_1
#define RGB_DMA_CH              DMA1_Channel1
#define RGB_DMA_IRQ             DMA1_Channel1_IRQn
#define RGB_DMA_IRQHandler      DMA1_Channel1_IRQHandler
//audio
#define HEAD_DET_GPIO_PORT               GPIOA
#define HEAD_DET_GPIO_PIN                GPIO_PIN_5
#define TAS2505_RST_GPIO_PORT            GPIOH
#define TAS2505_RST_GPIO_PIN             GPIO_PIN_10
//USB_SD
#define BTIM_TIMX_INT                    TIM6
#define BTIM_TIMX_INT_IRQn               TIM6_IRQn
#define BTIM_TIMX_INT_IRQHandler         TIM6_IRQHandler
#define BTIM_TIMX_INT_CLK_ENABLE()       __HAL_RCC_TIM6_CLK_ENABLE()
// USB connected
#define USB_CONNECTED_Pin               GPIO_PIN_5
#define USB_CONNECTED_GPIO_Port         GPIOH
// CHG_SWITCH
#define CHG_SWITCH_Pin GPIO_PIN_12
#define CHG_SWITCH_GPIO_Port GPIOB

#define CHG_STATUS_Pin GPIO_PIN_11
#define CHG_STATUS_GPIO_Port GPIOD

// SD NADA
#define SD_NA_D0_Pin               GPIO_PIN_8
#define SD_NA_D0_GPIO_Port         GPIOC
#define SD_NA_D0_AF                GPIO_AF9_SDIO1

#define SD_NA_D1_Pin               GPIO_PIN_9
#define SD_NA_D1_GPIO_Port         GPIOC
#define SD_NA_D1_AF                GPIO_AF9_SDIO1

#define SD_NA_D2_Pin               GPIO_PIN_10
#define SD_NA_D2_GPIO_Port         GPIOC
#define SD_NA_D2_AF                GPIO_AF9_SDIO1

#define SD_NA_D3_Pin               GPIO_PIN_11
#define SD_NA_D3_GPIO_Port         GPIOC
#define SD_NA_D3_AF                GPIO_AF9_SDIO1

#define SD_NA_CLK_Pin              GPIO_PIN_12
#define SD_NA_CLK_GPIO_Port        GPIOC
#define SD_NA_CLK_AF               GPIO_AF9_SDIO1

#define SD_NA_CMD_Pin              GPIO_PIN_2
#define SD_NA_CMD_GPIO_Port        GPIOD
#define SD_NA_CMD_AF               GPIO_AF9_SDIO1
// SD Card
    /**SDMMC2 GPIO Configuration
    PB4 (NJTRST)     ------> SDMMC2_D3
    PG11     ------> SDMMC2_D2
    PD6     ------> SDMMC2_CK
    PD7     ------> SDMMC2_CMD
    PB15     ------> SDMMC2_D1
    PB14     ------> SDMMC2_D0
    */
#define SD_PRESENT_Pin          GPIO_PIN_8
#define SD_PRESENT_GPIO_Port    GPIOH

#define SD_D0_Pin               GPIO_PIN_14
#define SD_D0_GPIO_Port         GPIOB
#define SD_D0_AF                GPIO_AF9_SDIO2

#define SD_D1_Pin               GPIO_PIN_15
#define SD_D1_GPIO_Port         GPIOB
#define SD_D1_AF                GPIO_AF9_SDIO2

#define SD_D2_Pin               GPIO_PIN_11
#define SD_D2_GPIO_Port         GPIOG
#define SD_D2_AF                GPIO_AF10_SDIO2

#define SD_D3_Pin               GPIO_PIN_4
#define SD_D3_GPIO_Port         GPIOB
#define SD_D3_AF                GPIO_AF9_SDIO2

#define SD_CLK_Pin              GPIO_PIN_6
#define SD_CLK_GPIO_Port        GPIOD
#define SD_CLK_AF               GPIO_AF11_SDIO2

#define SD_CMD_Pin              GPIO_PIN_7
#define SD_CMD_GPIO_Port        GPIOD
#define SD_CMD_AF               GPIO_AF11_SDIO2

//PPM
#define PPM_CONNECTED_Pin GPIO_PIN_2
#define PPM_CONNECTED_GPIO_Port GPIOB
#define PPM_OUT_Pin GPIO_PIN_8
#define PPM_OUT_GPIO_Port GPIOE //没有PWM输出
#define PSTR(s) ((const char *)(s))
#define F(s) (char *)(s)
// Debug
#define DEBUG_TX_Pin            GPIO_PIN_6
#define DEBUG_TX_GPIO_Port      GPIOB
#define DEBUG_TX_AF             GPIO_AF14_UART5
#define DEBUG_RX_Pin            GPIO_PIN_5
#define DEBUG_RX_GPIO_Port      GPIOB
#define DEBUG_RX_AF GPIO_AF14_UART5
#define DEBUG_UART              UART5
#define DEBUG_CLK()             __HAL_RCC_UART5_CLK_ENABLE()
#define DEBUG_PERCLK            RCC_PERIPHCLK_UART5
#define DEBUG_CLK_SELECTION     Usart234578ClockSelection
#define DEBUG_CLK_SELECTION_VAL RCC_USART234578CLKSOURCE_D2PCLK1

#endif

