#ifndef __BSP_ICM42607_H__
#define __BSP_ICM42607_H__

#include "main.h"
#include "i2c.h"
#ifdef __cplusplus
extern "C" {
#endif
#define ICM42607_I2C  &hi2c4

#define ICM42607_I2C_ADDRESS (0x68 << 1)

#define ONE_G 9.807f
 

#define ICM42607_I2C_TIMEOUT 		1000


/* 引脚定义 */

#define GYRO_INT_GPIO_PORT           GPIOG
#define GYRO_INT_GPIO_PIN            GPIO_PIN_13
#define GYRO_INT_GPIO_CLK_ENABLE()   do { __HAL_RCC_GPIOG_CLK_ENABLE(); } while (0)


#define GYRO_INT           ((HAL_GPIO_ReadPin(GYRO_INT_GPIO_PORT, GYRO_INT_GPIO_PIN) == GPIO_PIN_RESET) ? 0 : 1)


typedef struct icm42607_s
{
	uint16_t acc[3];
  uint16_t gyro[3];

}icm42607_t;
extern icm42607_t IMU;


void icm42607_init(void);


void read_icm42607_loop(void);
#ifdef __cplusplus
}
#endif
#endif //__TCA9539_H__
