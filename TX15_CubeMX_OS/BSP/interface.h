#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "main.h"
#include "bsp_lcd.h"
#include "gpio.h"
#include "bsp_key.h"
#include "bsp_tca9539.h"
#include "adc1.h"
#include "adc3.h"
#include "bsp_hall_stick.h"
#include "bsp_encoder.h"
#include "bsp_gt911.h"
#include "bsp_rtc.h"
extern uint32_t adc_s1;
extern uint32_t adc_s2;
extern uint32_t adc_bat;
void ADC_scan_Loop(void);
void Menu_Display_Loop(void);
void MP3_Menu_Display(void);
void color_test(void);
#endif /* __INTERFACE_H__ */

