
#include "board.h"
#include "driver_system_clock.h"
#include "adc.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "memorymap.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"
#include "tim.h"
#include "driver_delays.h"
void boardInit(void)
{
	MPU_Config();
	HAL_Init();
  SystemClock_Config();
  PeriphCommonClock_Config();
  MX_GPIO_Init();
	delaysInit(); //FreeRTOSר����ʱ
	pwrInit();
	pwrOn();
	
  MX_UART4_Init();
  MX_UART5_Init();
//  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();

  MX_DMA2D_Init();
  MX_I2C4_Init();
  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_FMC_Init();
//	extflash_test();

	lcdInit();
	keysInit();
	ledInit();
//	bsp_io_init();

			
	rotaryEncoderInit();
  touchPanelInit();
  //audioInit(&audioConfig);
  adcInit();
	debug_tx5("boardInit ok\n");
}

void boardOff(void)
{
  lcdOff();

//  while (pwrPressed()) {
//    WDG_RESET();
//  }

  SysTick->CTRL = 0; // turn off systick
	
	  // Shutdown the Haptic
  hapticDone();
	pwrOff();
//	while(1)
//	{
//		
//	}
}