
#include "driver_extflash.h"
#include "quadspi.h"
#include "usart.h"
#include <string.h>
#include <cstddef>

static const QSPI_CommandTypeDef cmd_write_en = {
	.Instruction = SPI_NOR_CMD_WREN,
	.InstructionMode = QSPI_INSTRUCTION_1_LINE
};

static int qspi_read(QSPI_CommandTypeDef* cmd, uint8_t* data, size_t size)
{
  cmd->NbData = size;
  int ret = HAL_QSPI_Command(&hqspi, cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);

  if (ret == HAL_OK) {
    ret = HAL_QSPI_Receive(&hqspi, data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
  }

  return ret == HAL_OK ? 0 : -1;
}

static int qspi_write(QSPI_CommandTypeDef* cmd, uint8_t* data, size_t size)
{
  cmd->NbData = size;
  int ret = HAL_QSPI_Command(&hqspi, cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);

  if (ret == HAL_OK) {
    ret = HAL_QSPI_Transmit(&hqspi, data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
  }

  return ret == HAL_OK ? 0 : -1;
}

static int qspi_read_status_register(uint8_t reg_num, uint8_t* value)
{
  QSPI_CommandTypeDef cmd = {
      .InstructionMode = QSPI_INSTRUCTION_1_LINE,
      .DataMode = QSPI_DATA_1_LINE,
  };

  switch(reg_num) {
    case 1:
      cmd.Instruction = SPI_NOR_CMD_RDSR;
      break;
    case 2:
      cmd.Instruction = SPI_NOR_CMD_RDSR2;
      break;
    default:
      return -1;
  }

  return qspi_read(&cmd, value, sizeof(value));
}

static int qspi_write_status_register(uint8_t reg_num, uint8_t value)
{
  QSPI_CommandTypeDef cmd = {
      .Instruction = SPI_NOR_CMD_WRSR,
      .InstructionMode = QSPI_INSTRUCTION_1_LINE,
      .DataMode = QSPI_DATA_1_LINE,
  };

  switch(reg_num) {
    case 1:
      cmd.Instruction = SPI_NOR_CMD_WRSR;
      break;
    case 2:
      // TODO: some parts can only write upper
      //       registers together with lower ones.
      cmd.Instruction = SPI_NOR_CMD_WRSR2;
      break;
    default:
      return -1;
  }

  return qspi_write(&cmd, &value, sizeof(value));
}

static int qspi_write_enable(void)
{
  int ret = HAL_QSPI_Command(&hqspi, (QSPI_CommandTypeDef*)&cmd_write_en,
                             HAL_QSPI_TIMEOUT_DEFAULT_VALUE);

  if (ret == HAL_OK) {
    uint8_t reg;
    do {
		  ret = qspi_read_status_register(1U, &reg);
	  } while (!ret && !(reg & SPI_NOR_WEL_BIT));
  }

  return ret == HAL_OK ? 0 : -1;
}

static int qspi_wait_until_ready(void)
{
  uint8_t reg;
  int ret;

  QSPI_CommandTypeDef cmd = {
      .Instruction = SPI_NOR_CMD_RDSR,
      .InstructionMode = QSPI_INSTRUCTION_1_LINE,
      .DataMode = QSPI_DATA_1_LINE,
  };

  do {
    ret = qspi_read(&cmd, &reg, sizeof(reg));
  } while (!ret && (reg & SPI_NOR_WIP_BIT));

  return ret;
}

static int qspi_enable_quad_io(void)
{
  uint8_t reg;

  if (qspi_read_status_register(QSPI_QE_REG, &reg) != 0) {
    return -1;
  }

  // check if already enabled
  if ((reg & QSPI_QE_BIT) != 0) {
    return 0;
  }

  // enable quad-io
  reg |= QSPI_QE_BIT;

  if (qspi_write_enable() != 0) return -1;

  if (qspi_write_status_register(QSPI_QE_REG, reg) != 0) {
    return -1;
  }

  if (qspi_wait_until_ready() != 0) return -1;

  // check if now enabled
  if (qspi_read_status_register(QSPI_QE_REG, &reg) != 0) {
    return -1;
  }

  return (reg & QSPI_QE_BIT) != 0 ? 0 : -1;
}

static _Bool qspi_is_memory_mapped(QSPI_HandleTypeDef* h)
{
  return ((READ_BIT(h->Instance->CCR, QUADSPI_CCR_FMODE) == QUADSPI_CCR_FMODE)
              ? 1: 0);
}

static int qspi_abort(QSPI_HandleTypeDef* h)
{
  if (HAL_QSPI_Abort(h) != HAL_OK) {
    return -1;
  }

  return 0;
}

int stm32_qspi_nor_memory_mapped(void)
{
  // assume quad mode / 3-byte address
  QSPI_CommandTypeDef cmd = {
    .Instruction = SPI_NOR_CMD_4READ,
    .AddressSize = QSPI_ADDRESS_24_BITS,
    .DummyCycles = QSPI_READ_DUMMY_CYCLES,
    .InstructionMode = QSPI_INSTRUCTION_1_LINE,
    .AddressMode = QSPI_ADDRESS_4_LINES,
    .DataMode = QSPI_DATA_4_LINES,
  };

  // not detectable via SFDP (apart from matching on part ID)
#if defined(QSPI_CONTINUOUS_READ)
  cmd.AlternateBytes = QSPI_CONTINUOUS_READ;
  cmd.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
  cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
  cmd.SIOOMode = QSPI_SIOO_INST_ONLY_FIRST_CMD;
#endif

  QSPI_MemoryMappedTypeDef mem_mapped = {
      .TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE,
  };

  if (HAL_QSPI_MemoryMapped(&hqspi, &cmd, &mem_mapped) != HAL_OK) {
    return -1;
  }

  return 0;
}

int stm32_qspi_nor_read(uint32_t address, void* data, uint32_t size)
{
  if (!qspi_is_memory_mapped(&hqspi)) {
    if (stm32_qspi_nor_memory_mapped() != 0) {
      return -1;
    }
  }

  uintptr_t mmap_addr = QSPI_BASE + address;
  memcpy(data, (void *)mmap_addr, size);

  return 0;
}

int stm32_qspi_nor_erase_sector(uint32_t address)
{
  // verify block alignment
  if (address & 0xFFFF) return -1;

  // backup & diable memory-mapped mode
  uint32_t qspi_ccr_backup = 0;
  if (qspi_is_memory_mapped(&hqspi)) {
    qspi_ccr_backup = READ_REG(hqspi.Instance->CCR);
    if (qspi_abort(&hqspi) != 0) return -1;
  }

  // write enable
  int ret = HAL_QSPI_Command(&hqspi, (QSPI_CommandTypeDef*)&cmd_write_en,
                             HAL_QSPI_TIMEOUT_DEFAULT_VALUE);

  if (ret == HAL_OK) {
    // block erase
    QSPI_CommandTypeDef s_command = {
        .Instruction = SPI_NOR_CMD_BE,
        .Address = (uint32_t)address,
        .AddressSize = QSPI_ADDRESS_24_BITS,
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .AddressMode = QSPI_ADDRESS_1_LINE,
    };
    ret = HAL_QSPI_Command(&hqspi, &s_command, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
  }

  if (ret == HAL_OK) {
    ret = qspi_wait_until_ready();
  }

  if (qspi_ccr_backup) {
    WRITE_REG(hqspi.Instance->CCR, qspi_ccr_backup);
  }

  return ret;
}

int stm32_qspi_nor_program(uint32_t address, void* data, uint32_t len)
{
  uint32_t qspi_ccr_backup = 0;
  if (qspi_is_memory_mapped(&hqspi)) {
    qspi_ccr_backup = READ_REG(hqspi.Instance->CCR);
    if (qspi_abort(&hqspi) != 0) return -1;
  }

  // write enable
  int ret = HAL_QSPI_Command(&hqspi, (QSPI_CommandTypeDef*)&cmd_write_en,
                             HAL_QSPI_TIMEOUT_DEFAULT_VALUE);

  // page program
  if (ret == HAL_OK) {
    QSPI_CommandTypeDef s_command = {
        .Instruction = SPI_NOR_CMD_PP_1_1_4,
        .Address = address,
        .AddressSize = QSPI_ADDRESS_24_BITS,
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .AddressMode = QSPI_ADDRESS_1_LINE,
        .DataMode = QSPI_DATA_4_LINES,
        .NbData = len,
    };
    ret = HAL_QSPI_Command(&hqspi, &s_command, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
  }

  // xmit data
  if (ret == HAL_OK) {
    ret = HAL_QSPI_Transmit(&hqspi, (uint8_t*)data,
                            HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
  }

  if (ret == HAL_OK) {
    ret = qspi_wait_until_ready();
  }

  if (qspi_ccr_backup) {
    WRITE_REG(hqspi.Instance->CCR, qspi_ccr_backup);
  }

  return ret;
}


int QSPI_GD25Q127_Identification(uint8_t id[3])
{
    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = 0x9F,
        .AddressMode = QSPI_ADDRESS_1_LINE,
        .Address = 0,
        .AddressSize = QSPI_ADDRESS_24_BITS,
        .DataMode = QSPI_DATA_1_LINE,
        .NbData = 3,
    };

    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return -1;
    }

    if (HAL_QSPI_Receive(&hqspi, id, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return -1;
    }
    return 0;
}

#define GD25Q127_SECTOR_SIZE (0x1000)   //擦除大小 4k
#define TEST_ADDR				0x0000
uint8_t DeviceID[2] = {0};
uint8_t RDID[3] = {0};
uint8_t IDNumber[8] = {0};
uint8_t test_write_buf[GD25Q127_SECTOR_SIZE] = {1,2,3,4,5,6,7,8,9};
uint8_t test_read_buf[GD25Q127_SECTOR_SIZE] ={0};
uint8_t sta1 = 0;
uint8_t sta2 = 0;
void extflash_test(void)
{
		uint32_t ExecutionTime_Begin;		// 开始时间
	uint32_t ExecutionTime_End;		// 结束时间
	uint32_t ExecutionTime;				// 执行时间	
	float    ExecutionSpeed;			// 执行速度
	int sta = 0;
	uint32_t i  =0;
	
	QSPI_GD25Q127_Identification(RDID);
	debug_tx5("RDID = 0x%x%x%x\n",RDID[0],RDID[1],RDID[2]);
	// 1.擦除 >>>>>>>   
	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	sta = stm32_qspi_nor_erase_sector(TEST_ADDR);
	ExecutionTime_End		= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin; //ms
	if(sta ==0)
	{
		debug_tx5("EraseSector ok!time = %d ms\n",ExecutionTime);
	}
	
	// 2.写入 >>>>>>>    
	for(i=0;i< GD25Q127_SECTOR_SIZE;i++)
	{
		test_write_buf[i] = i;
	}	
	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms
//	sta = QSPI_GD25Q127_Write(test_read_buf, 0x00, GD25Q127_SECTOR_SIZE);
	sta = stm32_qspi_nor_program(TEST_ADDR, test_read_buf, GD25Q127_SECTOR_SIZE);
	ExecutionTime_End		= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin; //ms
	ExecutionSpeed = (GD25Q127_SECTOR_SIZE/ExecutionTime)*1000;
	debug_tx5("Write sta = %d",sta);
	if(sta ==0)
	{
		
		debug_tx5("Write ok!time = %d ms,Size =%d KB,speed = %0.2f KB/s\n",ExecutionTime,GD25Q127_SECTOR_SIZE/1024,ExecutionSpeed);
	}
	
	// 3.读出 >>>>>>>    

	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	sta = stm32_qspi_nor_read(TEST_ADDR,test_write_buf,GD25Q127_SECTOR_SIZE);
	ExecutionTime_End		= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin; //ms
	ExecutionSpeed = (GD25Q127_SECTOR_SIZE/ExecutionTime)*1000;
	debug_tx5("Read sta = %d",sta);
	if(sta ==0)
	{
		debug_tx5 ("Read buf[0,255] = [%d,%d]\r\n",test_read_buf[0],test_read_buf[255]);
		debug_tx5("Read ok!time = %d ms,Size =%d KB,speed = %0.2f KB/s\n",ExecutionTime,GD25Q127_SECTOR_SIZE/1024,ExecutionSpeed);
	}
}
