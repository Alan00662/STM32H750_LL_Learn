#ifndef __DRIVER_LCD_H__
#define __DRIVER_LCD_H__

#include "main.h"

#define HBP  ( 20 )
#define VBP  ( 10 )

#define HSW  ( 6 )
#define VSH  ( 2 )

#define HFP  ( 40 )
#define VFP  ( 10 )

#define LCD_DELAY()         LCD_Delay()

#define SET_IO_INPUT( PORT, PIN )            LL_GPIO_SetPinMode( PORT, PIN, LL_GPIO_MODE_INPUT )
#define SET_IO_OUTPUT( PORT, PIN )           LL_GPIO_SetPinMode( PORT, PIN, LL_GPIO_MODE_OUTPUT )

#define LCD_NRST_HIGH()               LL_GPIO_SetOutputPin(LCD_RESET_GPIO, LCD_RESET_GPIO_PIN)
#define LCD_NRST_LOW()                LL_GPIO_ResetOutputPin(LCD_RESET_GPIO, LCD_RESET_GPIO_PIN)

#define LCD_CS_HIGH()                 LL_GPIO_SetOutputPin(LCD_SPI_CS_GPIO, LCD_SPI_CS_GPIO_PIN)
#define LCD_CS_LOW()                  LL_GPIO_ResetOutputPin(LCD_SPI_CS_GPIO, LCD_SPI_CS_GPIO_PIN)

#define LCD_SCK_HIGH()                LL_GPIO_SetOutputPin(LCD_SPI_GPIO, LCD_SPI_SCK_GPIO_PIN)
#define LCD_SCK_LOW()                 LL_GPIO_ResetOutputPin(LCD_SPI_GPIO, LCD_SPI_SCK_GPIO_PIN)

#define LCD_MOSI_HIGH()               LL_GPIO_SetOutputPin(LCD_SPI_GPIO, LCD_SPI_MOSI_GPIO_PIN)
#define LCD_MOSI_LOW()                LL_GPIO_ResetOutputPin(LCD_SPI_GPIO, LCD_SPI_MOSI_GPIO_PIN)

#define LCD_MOSI_AS_INPUT()           SET_IO_INPUT( LCD_SPI_GPIO, LCD_SPI_MOSI_GPIO_PIN )
#define LCD_MOSI_AS_OUTPUT()          SET_IO_OUTPUT( LCD_SPI_GPIO, LCD_SPI_MOSI_GPIO_PIN )

#define LCD_READ_DATA_PIN()           LL_GPIO_IsInputPinSet(LCD_SPI_GPIO, LCD_SPI_MOSI_GPIO_PIN)


#endif

