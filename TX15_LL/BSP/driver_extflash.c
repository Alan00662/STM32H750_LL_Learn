
#include "driver_extflash.h"
#include "quadspi.h"



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

static int qspi_write_enable()
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

static int qspi_wait_until_ready()
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
