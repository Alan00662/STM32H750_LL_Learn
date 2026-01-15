#include "board.h"

void board_init(void)
{
  SCB->VTOR = 0x90000000;
  __enable_irq();
  HAL_Init();
  SCB_EnableICache();   
	SCB_EnableDCache();
  // SCB->CACR|=1<<2;
  MPU_Config();
  HAL_Init();
  SystemClock_Config();
  PeriphCommonClock_Config();
  MX_GPIO_Init();

  power_init();
  led_init();
  // power_on_check();
  POWER_ON();
  /**power on! */
  LED_BLUE_ON();
  Debug_init();
  MX_I2C4_Init();
  backlight_init();
  backlight_pwm(100);
  st7796_init();
  MX_LTDC_Init();
  MX_DMA2D_Init();
  MX_TIM6_Init();
  HAL_Delay(10);

  app_lvgl_init();
  HAL_TIM_Base_Start_IT(&htim6);
  Debug("Board Init Success!\r\n");

  LED_BLUE_OFF();
}
