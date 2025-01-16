#ifndef __BSP_IO_H__
#define __BSP_IO_H__

#include "main.h"
#include "driver_tca9539.h"
// Port expander 1 (0x74)
#define SWITCH_A_L PCA95XX_P14
#define SWITCH_A_H PCA95XX_P15
#define SWITCH_B_L PCA95XX_P12
#define SWITCH_B_H PCA95XX_P13
#define SWITCH_C_L PCA95XX_P10
#define SWITCH_C_H PCA95XX_P11
#define SWITCH_D_L PCA95XX_P6
#define SWITCH_D_H PCA95XX_P7
#define SWITCH_E_L PCA95XX_P16
#define SWITCH_E_H PCA95XX_P17
#define SWITCH_F_H PCA95XX_P4
#define SWITCH_F_L PCA95XX_P5

// Port expander 2 (0x75)
#define BSP_TR1U PCA95XX_PIN_13
#define BSP_TR1D PCA95XX_PIN_12

#define BSP_TR2U PCA95XX_PIN_11
#define BSP_TR2D PCA95XX_PIN_10

#define BSP_TR3L PCA95XX_PIN_15
#define BSP_TR3R PCA95XX_PIN_14

#define BSP_TR4L PCA95XX_PIN_9
#define BSP_TR4R PCA95XX_PIN_8

#define FSSWITCH_1 PCA95XX_P0
#define FSSWITCH_2 PCA95XX_P1
#define FSSWITCH_3 PCA95XX_P2
#define FSSWITCH_4 PCA95XX_P3
#define FSSWITCH_5 PCA95XX_P4
#define FSSWITCH_6 PCA95XX_P5

extern uint8_t isSwitch3Pos(uint8_t idx);

int bsp_io_init(void);
uint32_t bsp_io_read_switches(void);
uint32_t bsp_io_read_fs_switches(void);
uint32_t bsp_get_fs_switches(void);

struct stm32_switch_t;

typedef enum {
  SWITCH_HW_UP = 0,
  SWITCH_HW_MID,
  SWITCH_HW_DOWN,
}SwitchHwPos;

//SwitchHwPos bsp_get_switch_position(const stm32_switch_t *sw, SwitchCategory cat, uint8_t idx);


#endif

