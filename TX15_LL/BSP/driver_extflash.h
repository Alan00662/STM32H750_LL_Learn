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

// GD25Q127C: does not expose these via SFDP

#define QSPI_QE_REG 2

#define QSPI_QE_BIT (1 << 1)

// TODO: use SFDP to detect this
//       -> 3rd DWORD "Instruction / Mode Clocks / Dummy cycles"
//
// GD25Q127C: 2 mode clocks + 4 dummy cycles
#define QSPI_READ_DUMMY_CYCLES 6


int stm32_qspi_nor_memory_mapped(void);
int stm32_qspi_nor_read(uint32_t address, void* data, uint32_t len);

int stm32_qspi_nor_erase_sector(uint32_t address);
int stm32_qspi_nor_program(uint32_t address, void* data, uint32_t len);
void extflash_test(void);
#endif

