
#include "bsp_key.h"
#include "bsp_led.h"
#include "usart.h"

uint8_t power_flg = 0;
void KEY_GPIO_init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOI);
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOH);

	/**/
	GPIO_InitStruct.Pin = ENTER_Pin|PAGE_L_Pin|RTN_Pin|TELE_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	/**/
	GPIO_InitStruct.Pin = MDL_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Init(MDL_GPIO_Port, &GPIO_InitStruct);
  
    /**/
	GPIO_InitStruct.Pin = PAGE_R_Pin|PWR_KEY_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/**/
	GPIO_InitStruct.Pin = SYS_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Init(SYS_GPIO_Port, &GPIO_InitStruct);
	
}

key_info_t Key_info = {0};
uint32_t key_scan_tick = 0;
void key_scan_Loop(void)
{
	static uint8_t power_cnt = 0;
	if((millis() - key_scan_tick) > 6)
	{
		Key_info.enter = KEY_ENTER;
		Key_info.left = KEY_PAGE_L;
		Key_info.right = KEY_PAGE_R;
		Key_info.sys = KEY_SYS;
		Key_info.modle = KEY_MDL;
		Key_info.tele = KEY_TELE;
		Key_info.rtn = KEY_RTN;
		
		if(PWR_SWITCH == 0)
		{
			power_cnt ++;
			debug_tx5("key_cnt = %d\r\n",power_cnt);
			if(power_cnt>=100)
			{
				power_cnt = 0;
				debug_tx5("tuan off\r\n");
				while(1)
				{
					LED0(0);//นุตฦ
					LED1(0);	
					LED2(0);					
				}
				
			}
		}
		else if(PWR_SWITCH == 1)
		{
			power_cnt = 0;
		}
		
		key_scan_tick = millis();
	}
}


