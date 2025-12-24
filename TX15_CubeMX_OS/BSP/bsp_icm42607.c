#include "bsp_icm42607.h"




static void icm42607_reg_read(uint8_t reg,uint8_t* data,uint8_t len) 
{

    HAL_I2C_Mem_Read(ICM42607_I2C, ICM42607_I2C_ADDRESS, reg,
                     1, data, len, ICM42607_I2C_TIMEOUT);
}

static void icm42607_reg_write(uint8_t reg, uint8_t data) 
{
    uint8_t tmp;
		tmp = data;
    HAL_I2C_Mem_Write(ICM42607_I2C, ICM42607_I2C_ADDRESS, reg,
                      1, &tmp, sizeof(tmp), ICM42607_I2C_TIMEOUT);
}

static void icm42607_gpio_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    TCA9539_INT_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = GYRO_INT_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GYRO_INT_GPIO_PORT, &GPIO_InitStruct);

}


void read_accel(uint16_t acc[3])
{
	
	uint8_t	data[6] = {0};
	#if 0
	HAL_I2C_Mem_Read(ICM42607_I2C, ICM42607_I2C_ADDRESS, 0x0b,
                  sizeof(data), data, sizeof(data), ICM42607_I2C_TIMEOUT);
	#else
	icm42607_reg_read(0x0b,&data[0],1);
	icm42607_reg_read(0x0c,&data[1],1);
	icm42607_reg_read(0x0d,&data[2],1);
	icm42607_reg_read(0x0e,&data[3],1);
	icm42607_reg_read(0x0f,&data[4],1);
	icm42607_reg_read(0x10,&data[5],1);
	#endif
	acc[0] = (data[0]<<8) |data[1];
	acc[1] = (data[2]<<8) |data[3];
	acc[2] = (data[4]<<8) |data[5];

	
}

void read_gyro(uint16_t gyro[3])
{
	uint8_t	data[6] = {0};
	#if 0
	HAL_I2C_Mem_Read(ICM42607_I2C, ICM42607_I2C_ADDRESS, 0x11,
                  sizeof(data), data, sizeof(data), ICM42607_I2C_TIMEOUT);
	#else
	icm42607_reg_read(0x11,&data[0],1);
	icm42607_reg_read(0x12,&data[1],1);
	icm42607_reg_read(0x13,&data[2],1);
	icm42607_reg_read(0x14,&data[3],1);
	icm42607_reg_read(0x15,&data[4],1);
	icm42607_reg_read(0x16,&data[5],1);
	#endif
	gyro[0] = (data[0]<<8) |data[1];
	gyro[1] = (data[2]<<8) |data[3];
	gyro[2] = (data[4]<<8)|data[5];
}

icm42607_t IMU ={0};
uint32_t read_icm42607_tick = 0;
void read_icm42607_loop(void)
{
	if((HAL_GetTick() - read_icm42607_tick) > 10)
	{

		read_accel(IMU.acc);
		read_gyro(IMU.gyro);
//		debug_tx5("accX =%d,accY =%d,accZ =%d\n",IMU.acc[0],IMU.acc[1],IMU.acc[2]);
//		debug_tx5("groyX =%d,groyY =%d,groyZ =%d\n",IMU.groy[0],IMU.groy[1],IMU.groy[2]);
		read_icm42607_tick =  HAL_GetTick();
	}

}	
 

static void IMU_reg_config(void)
{
	uint8_t IMU_threshold_temp = 0;
	
	icm42607_reg_write(0x1f, 0x0F);
	icm42607_reg_write(0x23, 0x04);

	icm42607_reg_write(0x24, 0x21);
	icm42607_reg_write(0x20, 0x09);
	icm42607_reg_write(0x21, 0x09);
	icm42607_reg_write(0x06,0x03);
	icm42607_reg_write(0x2B,0x00);
	icm42607_reg_write(0x2C,0x07);

}

void icm42607_init(void)
{
	uint8_t id;
	icm42607_gpio_init();
	
	icm42607_reg_read(0x75,&id,1);
	debug_tx5("icm42607_id is 0x%x \n",id);
	if(id == 0x61)
	{
		debug_tx5("icm42607_init ok \n");
	}
	IMU_reg_config();
	
}