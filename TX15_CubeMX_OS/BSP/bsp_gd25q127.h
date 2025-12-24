
#ifndef __GD25Q127_H__
#define __GD25Q127_H__

#include "main.h"




#include <stdint.h>
#if USE_QSPI_TEST1
#define GD25Q127_FLASH_SIZE (16 * 1024 * 1024) //16M
//#define GD25Q127_BLOCK_SIZE (0x10000) //64k
#define GD25Q127_BLOCK_SIZE (0x8000) //32k
#define GD25Q127_SECTOR_SIZE (0x1000)   //擦除大小 4k
#define GD25Q127_PAGE_SIZE (0x100)	//256 byte

#define GD25Q127_WRITE_ENABLE (0x06)
/*
 * The Quad Enable (QE) bit is set to 1 by default in the factory, therefore the device supports Standard/Dual
SPI as well as Quad SPI after power on. This bit cannot be reset to 0.
 */
#define GD25Q127_INPUT_FAST_READ (0xEB)
#define GD25Q127_PAGE_PROGRAM (0x02)
#define GD25Q127_STATUS_REG1 (0x05)
#define GD25Q127_ENABLE_RESET (0x66)
#define GD25Q127_RESET_DEVICE (0x99)
#define GD25Q127_DEVICE_ID (0x90)
#define GD25Q127_RDID (0x9F)
#define GD25Q127_ID_NUMBER (0x4b)
#define GD25Q127_ERASE_SECTOR (0x20)

#define QSPI_OK 0
#define QSPI_ERROR -1

void QSPI_GD25Q127_Init();
int QSPI_GD25Q127_Reset();
int QSPI_GD25Q127_DeviceID(uint8_t id[2]);
int QSPI_GD25Q127_IDNumber(uint8_t id[8]);

/*
 * 擦除特定地址
 * SectorAddress必须是W25Q64JV_SECTOR_SIZE整数倍
 */
int QSPI_GD25Q127_EraseSector(uint32_t SectorAddress);

/*
 * 任意地址读取数据
 */
int QSPI_GD25Q127_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size);

/*
 * 在页范围内写数据,长度不能越界
 * 注意写之前要确保flash里面对应位置的数据全为0xFF
 */
int QSPI_GD25Q127_PageProgram(uint8_t *pData, uint32_t WriteAddr, uint32_t Size);
/*
 * 必须确保写的地址范围内的数据全部为0xFF
 * 具有自动换页的功能
 */
int QSPI_GD25Q127_Write_NoCheck(uint8_t *pData, uint32_t WriteAddr, uint32_t Size);
/*
 * 在地址空间内任意地址写任意长度(不超过地址空间)的数据
 */
int QSPI_GD25Q127_Write(uint8_t *pData, uint32_t WriteAddr, uint32_t Size);
int QSPI_GD25Q127_EnableMemoryMappedMode();
void QSPI_GD25Q127_Test(void);

#endif

int8_t QSPI_W25Qxx_Reset(void)	;
int8_t QSPI_W25Qxx_Test(void);
#endif /* __GD25Q127_H__ */
