
#include "bsp_key.h"
#include "bsp_motor.h"
#include "usart.h"
#include "bsp_tas2505.h"
uint8_t power_flg = 0;
void KEY_GPIO_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = KEY_PAGE_R_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_PAGE_R_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = KEY_SYS_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_SYS_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = KEY_MDL_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_MDL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = KEY_PAGE_L_GPIO_PIN | KEY_RTN_GPIO_PIN | KEY_ENTER_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = KEY_TELE_GPIO_PIN ;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

key_info_t Key_info = {0};
uint32_t key_scan_tick = 0;
void key_scan_Loop(void)
{
	uint8_t motor_contr = 0;
	
	static uint8_t power_cnt = 0;
	if((HAL_GetTick() - key_scan_tick) > 6)
	{
		Key_info.enter = KEY_ENTER;
		Key_info.left = KEY_PAGE_L;
		Key_info.right = KEY_PAGE_R;
		Key_info.sys = KEY_SYS;
		Key_info.modle = KEY_MDL;
		Key_info.tele = KEY_TELE;
		Key_info.rtn = KEY_RTN;
		
		motor_contr = (Key_info.modle == 0)? 1:0;
		#if Motor_USE_PWM
		if(Key_info.modle == 0)
		{
			Motor_pwm(70);
		}
		else
		{
			Motor_pwm(0);
		}
		
		#else
		Motor_Set(motor_contr);
		#endif
		
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
					HAL_GPIO_WritePin(PWR_OUT_GPIO_Port, PWR_OUT_Pin, GPIO_PIN_RESET);
//					BackLight_pwm(0);//πÿ∆¡ƒª
						TFT_BL(0);
					LED0(0);//πÿµ∆
					LED1(0);	
					LED2(0);
					I2S_Play_Stop();// πÿ“Ù¿÷
					
				}
				
			}
		}
		else if(PWR_SWITCH == 1)
		{
			power_cnt = 0;
		}
		key_scan_tick = HAL_GetTick();
	}
}


