#include "bsp_io.h"
#include "hal.h"
#include "driver_delays.h"

typedef struct bsp_io_expander_s {
    pca95xx_t exp;
    uint32_t mask;
    uint32_t state;
}bsp_io_expander;

//两个IO拓展芯片
static bsp_io_expander _io_switches;		//switch开关的
static bsp_io_expander _io_fs_switches;	//回弹按键的

static void _init_io_expander(bsp_io_expander* io, uint32_t mask)
{
  io->mask = mask;
  io->state = 0;
}

static uint32_t _read_io_expander(bsp_io_expander* io)
{
  uint16_t value = 0;
  if (pca95xx_read(&io->exp, io->mask, &value) == 0) {
    io->state = value;
  }
  return io->state;
}

static void _poll_switches(void *pvParameter1, uint32_t ulParameter2)
{
  (void)ulParameter2;
  bsp_io_expander* io = (bsp_io_expander*)pvParameter1;
  _read_io_expander(io);
}

int bsp_io_init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);

	GPIO_InitStruct.Pin = IO_RESET_GPIO_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(IO_RESET_GPIO, &GPIO_InitStruct);
		
	_init_io_expander(&_io_fs_switches, 0xFF3F);
	pca95xx_init(&_io_fs_switches.exp,I2C_Bus_1,0x74);
	_init_io_expander(&_io_switches, 0xFFF8);
	pca95xx_init(&_io_switches.exp,I2C_Bus_1,0x75);

	LL_GPIO_ResetOutputPin(IO_RESET_GPIO, IO_RESET_GPIO_PIN);
	delay_ms(100);
	LL_GPIO_SetOutputPin(IO_RESET_GPIO, IO_RESET_GPIO_PIN);
	
	bsp_io_read_switches();
  bsp_io_read_fs_switches();
}

uint32_t bsp_io_read_switches(void)
{
  return _read_io_expander(&_io_switches);
}

uint32_t bsp_io_read_fs_switches(void)
{
  return _read_io_expander(&_io_fs_switches);
}

uint32_t bsp_get_fs_switches(void)
{
  return _io_fs_switches.state;
}

typedef struct bsp_io_sw_def_s {
    uint32_t pin_high;
    uint32_t pin_low;
}bsp_io_sw_def;

static uint32_t RGB_OFFSET = (1 << 16); // first after bspio pins
static uint16_t soft2POSLogicalState = 0xFFFF;

static const bsp_io_sw_def _switch_defs[] = {
        { SWITCH_A_H, SWITCH_A_L },
        { SWITCH_B_H, SWITCH_B_L },
        { SWITCH_C_H, SWITCH_C_L },
        { SWITCH_D_H, SWITCH_D_L },
        { SWITCH_E_H, SWITCH_E_L },
        { SWITCH_F_H, SWITCH_F_L },
};
