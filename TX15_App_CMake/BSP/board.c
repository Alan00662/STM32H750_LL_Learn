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
  Debug("Board Init Success!\r\n");
  LED_BLUE_OFF();
}
