#ifndef __DRIVER_TCA9539_H__
#define __DRIVER_TCA9539_H__

#include "main.h"
#include "i2c.h"

#define PCA95XX_PIN_0 (1 << 0)
#define PCA95XX_PIN_1 (1 << 1)
#define PCA95XX_PIN_2 (1 << 2)
#define PCA95XX_PIN_3 (1 << 3)
#define PCA95XX_PIN_4 (1 << 4)
#define PCA95XX_PIN_5 (1 << 5)
#define PCA95XX_PIN_6 (1 << 6)
#define PCA95XX_PIN_7 (1 << 7)
#define PCA95XX_PIN_8 (1 << 8)
#define PCA95XX_PIN_9 (1 << 9)
#define PCA95XX_PIN_10 (1 << 10)
#define PCA95XX_PIN_11 (1 << 11)
#define PCA95XX_PIN_12 (1 << 12)
#define PCA95XX_PIN_13 (1 << 13)
#define PCA95XX_PIN_14 (1 << 14)
#define PCA95XX_PIN_15 (1 << 15)

#define PCA95XX_P0  PCA95XX_PIN_0
#define PCA95XX_P1  PCA95XX_PIN_1
#define PCA95XX_P2  PCA95XX_PIN_2
#define PCA95XX_P3  PCA95XX_PIN_3
#define PCA95XX_P4  PCA95XX_PIN_4
#define PCA95XX_P5  PCA95XX_PIN_5
#define PCA95XX_P6  PCA95XX_PIN_6
#define PCA95XX_P7  PCA95XX_PIN_7
#define PCA95XX_P10  PCA95XX_PIN_8
#define PCA95XX_P11  PCA95XX_PIN_9
#define PCA95XX_P12  PCA95XX_PIN_10
#define PCA95XX_P13  PCA95XX_PIN_11
#define PCA95XX_P14  PCA95XX_PIN_12
#define PCA95XX_P15  PCA95XX_PIN_13
#define PCA95XX_P16  PCA95XX_PIN_14
#define PCA95XX_P17  PCA95XX_PIN_15

typedef struct {
	uint8_t 			bus;
  uint16_t      addr;
  uint16_t      polarity;
  uint16_t      direction;
  uint16_t      output;
} pca95xx_t;

int pca95xx_init(pca95xx_t* dev, uint8_t bus, uint16_t addr);
int pca95xx_read(pca95xx_t* dev, uint16_t mask, uint16_t* value);

#endif

