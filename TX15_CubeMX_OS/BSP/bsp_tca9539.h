#ifndef __TCA9539_H__
#define __TCA9539_H__

#include "main.h"
#include "i2c.h"
#ifdef __cplusplus
extern "C" {
#endif
#define IO_EXPANDER_I2C  &hi2c4
#define TCA9539_SW_I2C_ADDRESS (0x75 << 1)

#define TCA9539_KEY_I2C_ADDRESS (0x74 << 1)

#define TCA9539_INPUT_PORT_0_REG_ADDR 0x00
#define TCA9539_INPUT_PORT_1_REG_ADDR 0x01
#define TCA9539_OUTPUT_PORT_0_REG_ADDR 0x02
#define TCA9539_OUTPUT_PORT_1_REG_ADDR 0x03
#define TCA9539_INVERT_PORT_0_REG_ADDR 0x04
#define TCA9539_INVERT_PORT_1_REG_ADDR 0x05
#define TCA9539_CONFIG_PORT_0_REG_ADDR 0x06
#define TCA9539_CONFIG_PORT_1_REG_ADDR 0x07

#define TC9539_I2C_TIMEOUT 		1000

/* 引脚定义 */
#define SWITCH_RES_GPIO_PORT          GPIOJ
#define SWITCH_RES_GPIO_PIN           GPIO_PIN_4
#define SWITCH_RES_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)


#define TCA9539_INT_GPIO_PORT           GPIOD
#define TCA9539_INT_GPIO_PIN            GPIO_PIN_3
#define TCA9539_INT_GPIO_CLK_ENABLE()   do { __HAL_RCC_GPIOD_CLK_ENABLE(); } while (0)


#define SWITCH_INT           ((HAL_GPIO_ReadPin(PCF8574_INT_GPIO_PORT, PCF8574_INT_GPIO_PIN) == GPIO_PIN_RESET) ? 0 : 1)


typedef struct tca9539_key_s
{
	uint8_t k1;
    uint8_t k2;
    uint8_t k3;
    uint8_t k4;
    uint8_t k5;
    uint8_t k6;
}tca9539_key_t;
extern tca9539_key_t Tca9539;

typedef struct tca9539_switch_s
{
	uint8_t SAL;
    uint8_t SAH;
    uint8_t SA;
    uint8_t SBL;
    uint8_t SBH;
    uint8_t SB;
    uint8_t SCL;
    uint8_t SCH;
    uint8_t SC;
    uint8_t SDL;
    uint8_t SDH;
    uint8_t SD;
	uint8_t SEL;
    uint8_t SEH;
    uint8_t SE;
    uint8_t SFL;
    uint8_t SFH;
    uint8_t SF;
}tca9539_switch_t;
extern tca9539_switch_t Tca9539_sw;

typedef struct trim_info
{
    uint8_t rvu;  /* data */
    uint8_t rvd; /* data */
    uint8_t rhr;   /* data */
    uint8_t rhl; /* data */
    uint8_t lvu;  /* data */
    uint8_t lvd; /* data */
    uint8_t lhr;   /* data */
    uint8_t lhl; /* data */
} trim_info_t;
extern trim_info_t Trim_info;

void tca9539_init(void);
/**
 * @brief Driver for the TCA9539 IO Expander
 */

/**
 * @brief Configures each pin as input or output
 * @param io0 Bit mask for Port 0 pins (1=Input, 0=Output) 引脚设置成输入还是输出
 * @param io1 Bit mask for Port 1 pins (1=Input, 0=Output)
 */
void tca9539_configure(uint8_t io0, uint8_t io1);

/**
 * @brief Sets the outputs for each pin. If a pin is not configured as output, nothing will happen
 * @param io0 Bit mask for Port 0 pins
 * @param io1 Bit mask for Port 1 pins
 */
void tca9539_setOutputs(uint8_t io0, uint8_t io1);

/**
 * Clears any pending interrupts by reading from both IO ports
 */

void Read_TCP9539_Loop(void);
#ifdef __cplusplus
}
#endif
#endif //__TCA9539_H__
