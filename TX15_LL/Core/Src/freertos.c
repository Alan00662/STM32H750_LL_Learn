/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "board.h"
#include "driver_delays.h"
/* Definitions for defaultTask */
osThreadId_t ExtIoTaskHandle;
const osThreadAttr_t IoTask_attributes = {
  .name = "ioTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Definitions for LedTask */
osThreadId_t LedTaskHandle;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

osThreadId_t KeysTaskHandle;
const osThreadAttr_t KeysTask_attributes = {
  .name = "KeysTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Definitions for LedTask */
osThreadId_t LcdMenuHandle;
const osThreadAttr_t LcdMenu_attributes = {
  .name = "LcdMenu",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Definitions for LedTask */
osThreadId_t AdcTaskHandle;
const osThreadAttr_t Adc_attributes = {
  .name = "Adc",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

void EXT_IO_Task(void *argument);
void led_task(void *argument);
void keys_task(void *argument);
void Adc_task(void *argument);
void lcd_menu_task(void *argument);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {

  ExtIoTaskHandle = osThreadNew(EXT_IO_Task, NULL, &IoTask_attributes);
  LedTaskHandle = osThreadNew(led_task, NULL, &LedTask_attributes);
  LcdMenuHandle = osThreadNew(lcd_menu_task, NULL, &LcdMenu_attributes);
	KeysTaskHandle = osThreadNew(keys_task, NULL, &KeysTask_attributes);
	AdcTaskHandle = osThreadNew(Adc_task, NULL, &Adc_attributes);

}


void EXT_IO_Task(void *argument)
{

  for(;;)
  {
    osDelay(1);
  }

}



void led_task(void *argument)
{
	static uint8_t bink_num = 0;
	for(;;)
  { 
		switch(bink_num)
		{
			case 0:
				GPIO_LED_GPIO_ON(LED_RED_GPIO,LED_RED_GPIO_PIN);
				GPIO_LED_GPIO_OFF(LED_BLUE_GPIO,LED_BLUE_GPIO_PIN);
				GPIO_LED_GPIO_OFF(LED_GREEN_GPIO,LED_GREEN_GPIO_PIN);
				bink_num ++;
				break;
			case 1:
				GPIO_LED_GPIO_OFF(LED_RED_GPIO,LED_RED_GPIO_PIN);
				GPIO_LED_GPIO_ON(LED_BLUE_GPIO,LED_BLUE_GPIO_PIN);
				GPIO_LED_GPIO_OFF(LED_GREEN_GPIO,LED_GREEN_GPIO_PIN);
				bink_num ++;
				break;
			case 2:
				GPIO_LED_GPIO_OFF(LED_RED_GPIO,LED_RED_GPIO_PIN);
				GPIO_LED_GPIO_OFF(LED_BLUE_GPIO,LED_BLUE_GPIO_PIN);
				GPIO_LED_GPIO_ON(LED_GREEN_GPIO,LED_GREEN_GPIO_PIN);
				bink_num =0;
				break;
		}
    osDelay(300);
  }

}

void keys_task(void *argument)
{
	static uint8_t power_off_flg = 0;
	for(;;)
	{
//		readKeys();
		if(pwrOffPressed())
		{
			power_off_flg++;
			if(power_off_flg > 100)
			{
				boardOff();
			}
		}
		else
		{
			power_off_flg = 0;
		}
		osDelay(10);
	}
}

void Adc_task(void *argument)
{
	for(;;)
	{
		
	}
}


void lcd_menu_task(void *argument)
{
	for(;;)
	{
		LCD_CS_HIGH();
		LCD_SCK_HIGH();
		LCD_MOSI_HIGH();
		osDelay(10);
		LCD_CS_LOW();
		LCD_SCK_LOW();
		LCD_MOSI_LOW();
		osDelay(10);
//		LCD_ST7365_On();
	}
}


