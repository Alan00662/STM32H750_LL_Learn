#ifndef __DRIVER_EXTFLASH_H__
#define __DRIVER_EXTFLASH_H__

#include "main.h"

#define QSPI_FLASH_SIZE                 (8 * 1024 * 1024)

#define QSPI_PRESCALER_MAX 255

#define SPI_NOR_WIP_BIT (1 << 0)
#define SPI_NOR_WEL_BIT (1 << 1)

#define SPI_NOR_CMD_WRSR     0x01
#define SPI_NOR_CMD_RDSR     0x05
#define SPI_NOR_CMD_WRSR2    0x31
#define SPI_NOR_CMD_RDSR2    0x35

#define SPI_NOR_CMD_WREN     0x06
#define SPI_NOR_CMD_PP_1_1_4 0x32
#define SPI_NOR_CMD_BE       0xD8

#define SPI_NOR_CMD_4READ    0xEB

#define QSPI_STATUS_REG 1

#endif

