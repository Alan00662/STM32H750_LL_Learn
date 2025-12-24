#include "bsp_tca9539.h"
#include "bsp_lcd.h"
uint8_t sw_tcp0 =0;
uint8_t sw_tcp1 =0;
uint8_t key_tcp0 =0;
uint8_t key_tcp1 =0;

trim_info_t Trim_info = {0};
tca9539_switch_t Tca9539_sw;
tca9539_key_t Tca9539;

void tca9539_configure(uint8_t io0, uint8_t io1) 
{


   HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_SW_I2C_ADDRESS, TCA9539_CONFIG_PORT_0_REG_ADDR,
                     1, &io0, 1, TC9539_I2C_TIMEOUT);

   HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_SW_I2C_ADDRESS, TCA9539_CONFIG_PORT_1_REG_ADDR,
                     1, &io1, 1, TC9539_I2C_TIMEOUT);

	HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_KEY_I2C_ADDRESS, TCA9539_CONFIG_PORT_0_REG_ADDR,
                     1, &io0, 1, TC9539_I2C_TIMEOUT);

   HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_KEY_I2C_ADDRESS, TCA9539_CONFIG_PORT_1_REG_ADDR,
                     1, &io1, 1, TC9539_I2C_TIMEOUT);

}

void tca9539_clearInterrupts() 
{
    uint8_t tmp;
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_SW_I2C_ADDRESS, TCA9539_INPUT_PORT_0_REG_ADDR,
                     1, &tmp, sizeof(tmp), TC9539_I2C_TIMEOUT);
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_SW_I2C_ADDRESS, TCA9539_INPUT_PORT_1_REG_ADDR,
                     1, &tmp, sizeof(tmp), TC9539_I2C_TIMEOUT);
	
	HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_KEY_I2C_ADDRESS, TCA9539_INPUT_PORT_0_REG_ADDR,
                     1, &tmp, sizeof(tmp), TC9539_I2C_TIMEOUT);
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_KEY_I2C_ADDRESS, TCA9539_INPUT_PORT_1_REG_ADDR,
                     1, &tmp, sizeof(tmp), TC9539_I2C_TIMEOUT);
}

void tca9539_setOutputs(uint8_t io0, uint8_t io1) {
    uint8_t Data;
    Data = io0;
    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_SW_I2C_ADDRESS, TCA9539_OUTPUT_PORT_0_REG_ADDR,
                      1, &Data, 1, TC9539_I2C_TIMEOUT);
    Data = io1;
    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_SW_I2C_ADDRESS, TCA9539_OUTPUT_PORT_1_REG_ADDR,
                      1, &Data, 1, TC9539_I2C_TIMEOUT);
	
	Data = io0;
	HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_KEY_I2C_ADDRESS, TCA9539_OUTPUT_PORT_0_REG_ADDR,
                      1, &Data, 1, TC9539_I2C_TIMEOUT);
    Data = io1;
    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_KEY_I2C_ADDRESS, TCA9539_OUTPUT_PORT_1_REG_ADDR,
                      1, &Data, 1, TC9539_I2C_TIMEOUT);

}

void tca9539_sw_readInputs(uint8_t* io0, uint8_t* io1) {
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_SW_I2C_ADDRESS, TCA9539_INPUT_PORT_0_REG_ADDR,
                     1, io0, 1, TC9539_I2C_TIMEOUT);

    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_SW_I2C_ADDRESS, TCA9539_INPUT_PORT_1_REG_ADDR,
                     1, io1, 1, TC9539_I2C_TIMEOUT);
}

void tca9539_key_readInputs(uint8_t* io0, uint8_t* io1) {
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_KEY_I2C_ADDRESS, TCA9539_INPUT_PORT_0_REG_ADDR,
                     1, io0, 1, TC9539_I2C_TIMEOUT);

    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_KEY_I2C_ADDRESS, TCA9539_INPUT_PORT_1_REG_ADDR,
                     1, io1, 1, TC9539_I2C_TIMEOUT);
}



static void tca9539_gpio_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    SWITCH_RES_GPIO_CLK_ENABLE();
    TCA9539_INT_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = SWITCH_RES_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SWITCH_RES_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TCA9539_INT_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TCA9539_INT_GPIO_PORT, &GPIO_InitStruct);

}

void tca9539_init(void)
{
	tca9539_gpio_init();
    HAL_GPIO_WritePin(SWITCH_RES_GPIO_PORT, SWITCH_RES_GPIO_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(SWITCH_RES_GPIO_PORT, SWITCH_RES_GPIO_PIN, GPIO_PIN_SET);
	tca9539_configure(0xff,0xff);
	tca9539_clearInterrupts();
}


static void tca9539_sw_read_bit(void)
{
    tca9539_sw_readInputs(&sw_tcp0,&sw_tcp1);
	
	Tca9539_sw.SDH = (sw_tcp0 & 0x80) >> 7;
    Tca9539_sw.SDL = (sw_tcp0 & 0x40) >> 6;
    Tca9539_sw.SFL = (sw_tcp0 & 0x20) >> 5;
    Tca9539_sw.SFH = (sw_tcp0 & 0x10) >> 4;

    Tca9539_sw.SEL = (sw_tcp1 & 0x80) >> 7;
    Tca9539_sw.SEH = (sw_tcp1 & 0x40) >> 6;
    Tca9539_sw.SAH = (sw_tcp1 & 0x20) >> 5;
    Tca9539_sw.SAL = (sw_tcp1 & 0x10) >> 4;
    Tca9539_sw.SBH = (sw_tcp1 & 0x08) >> 3;
    Tca9539_sw.SBL = (sw_tcp1 & 0x04) >> 2;
    Tca9539_sw.SCH = (sw_tcp1 & 0x02) >> 1;
    Tca9539_sw.SCL =  sw_tcp1 & 0x01;
	
	Tca9539_sw.SA = (Tca9539_sw.SAL == 0 ? 1 : (Tca9539_sw.SAH == 0 ? 3 : 2));
	Tca9539_sw.SB = (Tca9539_sw.SBL == 0 ? 1 : (Tca9539_sw.SBH == 0 ? 3 : 2));
	Tca9539_sw.SC = (Tca9539_sw.SCL == 0 ? 1 : (Tca9539_sw.SCH == 0 ? 3 : 2));
	Tca9539_sw.SD = (Tca9539_sw.SDL == 0 ? 1 : (Tca9539_sw.SDH == 0 ? 3 : 2));
	Tca9539_sw.SE = (Tca9539_sw.SEL == 0 ? 1 : (Tca9539_sw.SEH == 0 ? 0 : 1));
	Tca9539_sw.SF = (Tca9539_sw.SFL == 0 ? 1 : (Tca9539_sw.SFH == 0 ? 0 : 1));
}


static void tca9539_key_read_bit(void)
{
    tca9539_key_readInputs(&key_tcp0,&key_tcp1);
    Tca9539.k6 = (key_tcp0 & 0x20) >> 5;
    Tca9539.k5 = (key_tcp0 & 0x10) >> 4;
    Tca9539.k4 = (key_tcp0 & 0x08) >> 3;
    Tca9539.k3 = (key_tcp0 & 0x04) >> 2;
    Tca9539.k2 = (key_tcp0 & 0x02) >> 1;   //P01
    Tca9539.k1 =  key_tcp0 & 0x01;			//P00

    Trim_info.lhl = (key_tcp1 & 0x80) >> 7;
    Trim_info.lhr = (key_tcp1 & 0x40) >> 6;
    Trim_info.lvu = (key_tcp1 & 0x20) >> 5;
    Trim_info.lvd = (key_tcp1 & 0x10) >> 4;
    Trim_info.rvu = (key_tcp1 & 0x08) >> 3;
    Trim_info.rvd = (key_tcp1 & 0x04) >> 2;
    Trim_info.rhl = (key_tcp1 & 0x02) >> 1;
    Trim_info.rhr =  key_tcp1 & 0x01; 			//P10	

}

uint32_t tcp9539_switch_tick = 0;
void Read_TCP9539_Loop(void)
{
	if((HAL_GetTick() - tcp9539_switch_tick) > 15)
	{
		static uint8_t backlight_add_cnt = 0;
		static uint8_t backlight_dic_cnt = 0;
		tca9539_sw_read_bit();
		tca9539_key_read_bit();
		if(Trim_info.rhr == 0)
		{
			backlight_add_cnt++;
//			if(backlight_add_cnt >= 6)
//			{
//				backlight_add_cnt = 0;
//				backlight_pwm += 1;
//				if(backlight_pwm > 100)
//				{
//					backlight_pwm = 100;
//				}
//			}
		}
		else
		{
			if(backlight_add_cnt >= 6)
			{
				backlight_add_cnt = 0;
				backlight_pwm += 1;
				if(backlight_pwm > 100)
				{
					backlight_pwm = 100;
				}
			}
		}
		if(Trim_info.rhl == 0)
		{
			backlight_dic_cnt--;
//			if(backlight_dic_cnt >= 6)
//			{
//				backlight_dic_cnt = 0;
//				backlight_pwm -= 1;
////				if(backlight_pwm < 10)
////				{
////					backlight_pwm = 10;
////				}
//								if(backlight_pwm < 1)
//				{
//					backlight_pwm = 0;
//				}
//			}
		}
		else
		{
			if(backlight_dic_cnt >= 6)
			{
				backlight_dic_cnt = 0;
				backlight_pwm -= 1;
				if(backlight_pwm < 2)
				{
					backlight_pwm = 1;
				}
			}
		}
		BackLight_pwm(backlight_pwm);
#if USE_LED_TEST		
		if(Tca9539_sw.SD == 1)
		{
				LED0(1);
				LED1(0);
				LED2(0);
		}
		else if(Tca9539_sw.SD == 2)
		{
				LED0(0);
				LED1(1);
				LED2(0);
		}
		else if(Tca9539_sw.SD == 3)
		{
				LED0(0);
				LED1(0);
				LED2(1);
		}
#endif
		tcp9539_switch_tick =  HAL_GetTick();
	}

}	
/*******ÁíÒ»¸ötca9539*******/


