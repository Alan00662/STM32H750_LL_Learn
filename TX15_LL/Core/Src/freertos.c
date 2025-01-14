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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
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



void StartDefaultTask(void *argument);
void led_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {


  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of LedTask */
  LedTaskHandle = osThreadNew(led_task, NULL, &LedTask_attributes);


}


void StartDefaultTask(void *argument)
{

  for(;;)
  {
    osDelay(1);
  }

}



void led_task(void *argument)
{
	static uint8_t bink_flg = 0;
	for(;;)
  { 
		switch(bink_flg)
		{
			case 0:
				LED0(1);
				LED1(0);
				LED2(0);
				bink_flg ++;
				break;
			case 1:
				LED0(0);
				LED1(1);
				LED2(0);
				bink_flg ++;
				break;
			case 2:
				LED0(0);
				LED1(0);
				LED2(1);
				bink_flg =0;
				break;
		}
    osDelay(300);
  }

}



