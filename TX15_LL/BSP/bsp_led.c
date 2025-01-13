
#include "bsp_led.h"


uint32_t led0_bink_tick = 0;
void led0_bink(uint16_t ms)
{
	if((millis() - led0_bink_tick) > ms)
	{
		LL_GPIO_TogglePin(LED1_GPIO_Port, LED0_Pin);
		led0_bink_tick =  millis();
	}

}	

uint32_t led1_bink_tick = 0;
void led1_bink(uint16_t ms)
{
	if((millis() - led1_bink_tick) > ms)
	{
		LL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		led1_bink_tick =  millis();
	}

}	

uint32_t led2_bink_tick = 0;
void led2_bink(uint16_t ms)
{
	if((millis() - led2_bink_tick) > ms)
	{
		LL_GPIO_TogglePin(LED1_GPIO_Port, LED2_Pin);
		led2_bink_tick =  millis();
	}

}	

uint32_t led_Loop_bink_tick = 0;
void led_Loop_bink(uint16_t ms)
{
	static uint8_t bink_flg = 0;
	if((millis() - led_Loop_bink_tick) > ms)
	{
		switch(bink_flg)
		{
			case 0:
				LED0(1);
				LED1(0);
				LED2(0);
				bink_flg =1;
				break;
			case 1:
				LED0(0);
				LED1(1);
				LED2(0);
				bink_flg =2;
				break;
			case 2:
				LED0(0);
				LED1(0);
				LED2(1);
				bink_flg =0;
				break;
		}
							
		led_Loop_bink_tick =  millis();
	}

}	
