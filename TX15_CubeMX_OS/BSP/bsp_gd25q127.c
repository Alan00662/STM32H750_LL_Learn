
#include "stm32h7xx.h" // Device header
#include "bsp_gd25q127.h"
#include "main.h"
#include <string.h>

extern QSPI_HandleTypeDef hqspi;

#if USE_QSPI_TEST1
/*
 * 写操作时先读取内部数据
 */
static uint8_t GD25Q127_buf[GD25Q127_SECTOR_SIZE];

/**
 * @brief 自动轮询等待内存准备好
 * @param timeout 超时时间
 * @return 0: 成功; 其他: 失败
 */
static int QSPI_GD25Q127_AutoPollingMemReady(uint32_t timeout)
{

    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_STATUS_REG1,
        .DataMode = QSPI_DATA_1_LINE,
    };

    QSPI_AutoPollingTypeDef conf = {
        .Match = 0x00,
        .Mask = 0x01,
        .MatchMode = QSPI_MATCH_MODE_AND,
        .StatusBytesSize = 1,
        .Interval = 0x10,
        .AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE,
    };

    if (HAL_QSPI_AutoPolling(&hqspi, &cmd, &conf, timeout) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/**
 * @brief 写使能
 * @return 0: 成功; 其他: 失败
 */
static int QSPI_GD25Q127_WriteEnable(void)
{

    QSPI_CommandTypeDef cmd = {
        .InstructionMode   = QSPI_INSTRUCTION_1_LINE,
        .Instruction 	   = GD25Q127_WRITE_ENABLE,
//		.AddressMode       = QSPI_ADDRESS_NONE,
//		.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE,
//		.DataMode 		   = QSPI_DATA_1_LINE,
//		.DummyCycles 	   = 0,
//		.DdrMode           = QSPI_DDR_MODE_DISABLE,
//		.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY,
//		.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD
    };

    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25Q127_STATUS_REG1;

    cmd.DataMode = QSPI_DATA_1_LINE;
    cmd.DummyCycles = 0;
    cmd.NbData = 0;

    QSPI_AutoPollingTypeDef conf = {
        .Match = 0x02,
        .Mask = 0x02,
        .MatchMode = QSPI_MATCH_MODE_AND,
        .StatusBytesSize = 1,
        .Interval = 0x10,
        .AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE,
    };

    if (HAL_QSPI_AutoPolling(&hqspi, &cmd, &conf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}
uint8_t ret = 0;
void QSPI_GD25Q127_Init(void)
{
   ret = QSPI_GD25Q127_Reset();

}

/**
 * @brief 复位GD25Q127
 * @return 0: 成功; 其他: 失败
 */
int QSPI_GD25Q127_Reset()
{

    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_ENABLE_RESET,
    };

    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    cmd.Instruction = GD25Q127_RESET_DEVICE;
    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (QSPI_GD25Q127_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/**
 * @brief 擦除
 * @param pID 存放ID的指针
 * @return 0: 成功; 其他: 失败
 */
int QSPI_GD25Q127_EraseSector(uint32_t SectorAddress)
{
    if (QSPI_GD25Q127_WriteEnable() != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_ERASE_SECTOR,
        .AddressMode = QSPI_ADDRESS_1_LINE,
        .Address = SectorAddress,
        .AddressSize = QSPI_ADDRESS_24_BITS,
    };

    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (QSPI_GD25Q127_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/**
 * @brief 读取数据
 * @param pData 存放数据的指针
 * @param ReadAddr 读取地址
 * @param Size 读取长度
 * @return 0: 成功; 其他: 失败
 */
int QSPI_GD25Q127_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
    if (QSPI_GD25Q127_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_INPUT_FAST_READ,
        .AddressMode = QSPI_ADDRESS_4_LINES,
        .Address = ReadAddr,
        .AddressSize = QSPI_ADDRESS_24_BITS,
		
		.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE,
//        .AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES,
//        .AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS,
//        .AlternateBytes = 0xF0, // datasheet p22
		
        .DataMode = QSPI_DATA_4_LINES,
        .DummyCycles = 4,
        .NbData = Size,
    };

    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (QSPI_GD25Q127_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/**
 * @brief 写入数据
 * @param pData 存放数据的指针
 * @param WriteAddr 写入地址
 * @param Size 写入长度
 * @return 0: 成功; 其他: 失败
 */
int QSPI_GD25Q127_PageProgram(uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
    if (QSPI_GD25Q127_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    if (QSPI_GD25Q127_WriteEnable() != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_PAGE_PROGRAM,
        .AddressMode = QSPI_ADDRESS_1_LINE,
        .Address = WriteAddr,
        .AddressSize = QSPI_ADDRESS_24_BITS,
        .DataMode = QSPI_DATA_1_LINE,
        .DummyCycles = 0,
        .NbData = Size,
    };
    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (HAL_QSPI_Transmit(&hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (QSPI_GD25Q127_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/**
 * @brief 写入数据，不检查扇区是否擦除
 * @param pData 存放数据的指针
 * @param WriteAddr 写入地址
 * @param Size 写入长度
 * @return 0: 成功; 其他: 失败
 */
int QSPI_GD25Q127_Write_NoCheck(uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
    int ret = QSPI_OK;
    uint32_t pageremain = GD25Q127_PAGE_SIZE - WriteAddr % GD25Q127_PAGE_SIZE;
    if (Size <= pageremain)
    {
        pageremain = Size;
    }
    while (1)
    {
        ret = QSPI_GD25Q127_PageProgram(pData, WriteAddr, pageremain);
        if (ret != QSPI_OK || Size == pageremain)
            break;
        pData += pageremain;
        WriteAddr += pageremain;
        Size -= pageremain;
        pageremain = Size > GD25Q127_PAGE_SIZE ? GD25Q127_PAGE_SIZE : Size;
    }
    return ret;
}

/**
 * @brief 写入数据，自动擦除扇区
 * @param pData 存放数据的指针
 * @param WriteAddr 写入地址    
 * @param Size 写入长度
 * @return 0: 成功; 其他: 失败  
 */
int QSPI_GD25Q127_Write(uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
    int ret = QSPI_OK;
    uint32_t secpos = WriteAddr / GD25Q127_SECTOR_SIZE;
    uint16_t secoff = WriteAddr % GD25Q127_SECTOR_SIZE;
    uint16_t secremain = GD25Q127_SECTOR_SIZE - secoff;
    uint32_t i;
    if (Size <= secremain)
        secremain = Size;
    while (1)
    {
        ret = QSPI_GD25Q127_Read(GD25Q127_buf, secpos * GD25Q127_SECTOR_SIZE, GD25Q127_SECTOR_SIZE);
        if (ret != QSPI_OK)
            break;
        for (i = 0; i < secremain; i++)
        {
            if (GD25Q127_buf[secoff + i] != 0xFF)
                break;
        }
        if (i < secremain)
        {
            ret = QSPI_GD25Q127_EraseSector(secpos * GD25Q127_SECTOR_SIZE);
            if (ret != QSPI_OK)
                break;
            memcpy(GD25Q127_buf + secoff, pData, secremain);
            ret = QSPI_GD25Q127_Write_NoCheck(GD25Q127_buf, secpos * GD25Q127_SECTOR_SIZE, GD25Q127_SECTOR_SIZE);
            if (ret != QSPI_OK)
                break;
        }
        else
        {
            ret = QSPI_GD25Q127_Write_NoCheck(pData, WriteAddr, secremain);
            if (ret != QSPI_OK)
                break;
        }
        if (Size == secremain)
            break;
        secpos++;
        secoff = 0;
        pData += secremain;
        WriteAddr += secremain;
        Size -= secremain;
        secremain = (Size - GD25Q127_SECTOR_SIZE) ? GD25Q127_SECTOR_SIZE : Size;
    }
    return ret;
}

int8_t QSPI_W25Qxx_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size)
{	
	uint32_t end_addr, current_size, current_addr;
	uint8_t *write_data;  // 要写入的数据

	current_size = GD25Q127_PAGE_SIZE - (WriteAddr % GD25Q127_PAGE_SIZE); // 计算当前页还剩余的空间

	if (current_size > Size)	// 判断当前页剩余的空间是否足够写入所有数据
	{
		current_size = Size;		// 如果足够，则直接获取当前长度
	}

	current_addr = WriteAddr;		// 获取要写入的地址
	end_addr = WriteAddr + Size;	// 计算结束地址
	write_data = pBuffer;			// 获取要写入的数据

	do
	{
		// 发送写使能
		if (QSPI_GD25Q127_WriteEnable() != QSPI_OK)
		{
			return QSPI_ERROR;
		}

		// 按页写入数据
		else if(QSPI_GD25Q127_PageProgram(write_data, current_addr, current_size) != QSPI_OK)
		{
			return QSPI_ERROR;
		}

		// 使用自动轮询标志位，等待写入的结束 
		else 	if (QSPI_GD25Q127_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
		{
			return QSPI_ERROR;
		}

		else // 按页写入数据成功，进行下一次写数据的准备工作
		{
			current_addr += current_size;	// 计算下一次要写入的地址
			write_data += current_size;	// 获取下一次要写入的数据存储区地址
			// 计算下一次写数据的长度
			current_size = ((current_addr + GD25Q127_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : GD25Q127_PAGE_SIZE;
		}
	}
	while (current_addr < end_addr) ; // 判断数据是否全部写入完毕

	return QSPI_OK;	// 写入数据成功

}

/**
 * @brief 使能内存映射模式
 * @return 0: 成功; 其他: 失败  
 */
int QSPI_GD25Q127_EnableMemoryMappedMode()
{
    QSPI_MemoryMappedTypeDef mem_mapped_cfg = {
        .TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE,
    };

    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_INPUT_FAST_READ,
        .AddressMode = QSPI_ADDRESS_4_LINES,
        .Address = 0,
        .AddressSize = QSPI_ADDRESS_24_BITS,
        .AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES,
        .AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS,
        .AlternateBytes = 0xf0, // datasheet p22
        .DataMode = QSPI_DATA_4_LINES,
        .DummyCycles = 4,
        .NbData = 0,
    };
    if (HAL_QSPI_MemoryMapped(&hqspi, &cmd, &mem_mapped_cfg) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/**
 * @brief 读取设备ID
 * @param id 存放ID的指针
 * @return 0: 成功; 其他: 失败
 */
int QSPI_GD25Q127_DeviceID(uint8_t id[2])
{
    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_DEVICE_ID,
        .AddressMode = QSPI_ADDRESS_1_LINE,
        .Address = 0,
        .AddressSize = QSPI_ADDRESS_24_BITS,
        .DataMode = QSPI_DATA_1_LINE,
        .NbData = 2,
    };

    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, id, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

int QSPI_GD25Q127_Identification(uint8_t id[3])
{
    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_RDID,
        .AddressMode = QSPI_ADDRESS_1_LINE,
        .Address = 0,
        .AddressSize = QSPI_ADDRESS_24_BITS,
        .DataMode = QSPI_DATA_1_LINE,
        .NbData = 3,
    };

    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, id, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/**
 * @brief 读取ID号
 * @param id 存放ID的指针
 * @return 0: 成功; 其他: 失败
 */
int QSPI_GD25Q127_IDNumber(uint8_t id[8])
{
    QSPI_CommandTypeDef cmd = {
        .InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .Instruction = GD25Q127_ID_NUMBER,
        .DataMode = QSPI_DATA_1_LINE,
        .DummyCycles = 4,
        .NbData = 8,
    };

    if (HAL_QSPI_Command(&hqspi, &cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, id, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

uint8_t DeviceID[2] = {0};
uint8_t RDID[3] = {0};
uint8_t IDNumber[8] = {0};
uint8_t test_write_buf[GD25Q127_SECTOR_SIZE] = {1,2,3,4,5,6,7,8,9};
uint8_t test_read_buf[GD25Q127_SECTOR_SIZE] ={0};
uint8_t sta1 = 0;
uint8_t sta2 = 0;
void QSPI_GD25Q127_Test(void)
{
	int sta = 0;
	uint32_t i  =0;
    QSPI_GD25Q127_DeviceID(DeviceID);//0xC8,0x17

	QSPI_GD25Q127_Identification(RDID);

	debug_tx5("DeviceID = 0x%x%x\n",DeviceID[0],DeviceID[1]);
	debug_tx5("RDID = 0x%x%x%x\n",RDID[0],RDID[1],RDID[2]);
	if (DeviceID[0] == 0xC8 && DeviceID[1] == 0x17)
	{
		uart5_send_string("QSPI_GD25Q127 init ok\n");
	}
	QSPI_GD25Q127_IDNumber(IDNumber);
	
	debug_tx5("IDNumber = 0x");	
	for(i = 0;i<8;i++)
	{
		
		debug_tx5("%x",IDNumber[i]);
	}
	debug_tx5("\n");	
//    QSPI_GD25Q127_Read(test_read_buf, 0x0, GD25Q127_SECTOR_SIZE);
//    for (int i = 0; i < GD25Q127_SECTOR_SIZE; i++)
//    {
//        test_buf[i] = i;
//    }
//    sta1 = QSPI_GD25Q127_Write(test_write_buf, 0x00, 9);
//	HAL_Delay(100);
//    sta2 = QSPI_GD25Q127_Read(test_read_buf, 0x00, 9);
	
	uint32_t ExecutionTime_Begin;		// 开始时间
	uint32_t ExecutionTime_End;		// 结束时间
	uint32_t ExecutionTime;				// 执行时间	
	float    ExecutionSpeed;			// 执行速度

// 1.擦除 >>>>>>>    
	
	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	sta = QSPI_GD25Q127_EraseSector(0x0000);
	ExecutionTime_End		= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin; //ms
	debug_tx5("EraseSector sta = %d",sta);
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
	sta = QSPI_W25Qxx_WriteBuffer(test_read_buf, 0x00, GD25Q127_SECTOR_SIZE);
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
	sta = QSPI_GD25Q127_Read(test_write_buf, 0x00, GD25Q127_SECTOR_SIZE);
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
#endif
#if USE_QSPI_TEST2

int8_t QSPI_W25Qxx_WriteEnable(void)
{
	QSPI_CommandTypeDef     s_command;	   // QSPI传输配置
	QSPI_AutoPollingTypeDef s_config;		// 轮询比较相关配置参数

	s_command.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;    	// 1线指令模式
	s_command.AddressMode 			= QSPI_ADDRESS_NONE;   		      // 无地址模式
	s_command.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;  	// 无交替字节 
	s_command.DdrMode           	= QSPI_DDR_MODE_DISABLE;      	// 禁止DDR模式
	s_command.DdrHoldHalfCycle  	= QSPI_DDR_HHC_ANALOG_DELAY;  	// DDR模式中数据延迟，这里用不到
	s_command.SIOOMode          	= QSPI_SIOO_INST_EVERY_CMD;		// 每次传输数据都发送指令	
	s_command.DataMode 				= QSPI_DATA_NONE;       	      // 无数据模式
	s_command.DummyCycles 			= 0;                   	         // 空周期个数
	s_command.Instruction	 		= W25Qxx_CMD_WriteEnable;      	// 发送写使能命令

	// 发送写使能命令
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) 
	{
		return W25Qxx_ERROR_WriteEnable;	//
	}
	
// 不停的查询 W25Qxx_CMD_ReadStatus_REG1 寄存器，将读取到的状态字节中的 W25Qxx_Status_REG1_WEL 不停的与 0x02 作比较
// 读状态寄存器1的第1位（只读），WEL写使能标志位，该标志位为1时，代表可以进行写操作
	
	s_config.Match           = 0x02;  								// 匹配值
	s_config.Mask            = W25Qxx_Status_REG1_WEL;	 		// 读状态寄存器1的第1位（只读），WEL写使能标志位，该标志位为1时，代表可以进行写操作
	s_config.MatchMode       = QSPI_MATCH_MODE_AND;			 	// 与运算
	s_config.StatusBytesSize = 1;									 	// 状态字节数
	s_config.Interval        = 0x10;							 		// 轮询间隔
	s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;	// 自动停止模式

	s_command.Instruction    = W25Qxx_CMD_ReadStatus_REG1;	// 读状态信息寄存器
	s_command.DataMode       = QSPI_DATA_1_LINE;					// 1线数据模式
	s_command.NbData         = 1;										// 数据长度

	// 发送轮询等待命令	
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; 	// 轮询等待无响应
	}	
	return QSPI_W25Qxx_OK;  // 通信正常结束
}

int8_t QSPI_W25Qxx_AutoPollingMemReady(void)
{
	QSPI_CommandTypeDef     s_command;	   // QSPI传输配置
	QSPI_AutoPollingTypeDef s_config;		// 轮询比较相关配置参数

	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;			// 1线指令模式
	s_command.AddressMode       = QSPI_ADDRESS_NONE;					// 无地址模式
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;			//	无交替字节 
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;	     	 	// 禁止DDR模式
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;	   	// DDR模式中数据延迟，这里用不到
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;	   	//	每次传输数据都发送指令	
	s_command.DataMode          = QSPI_DATA_1_LINE;						// 1线数据模式
	s_command.DummyCycles       = 0;											//	空周期个数
	s_command.Instruction       = W25Qxx_CMD_ReadStatus_REG1;	   // 读状态信息寄存器
																					
// 不停的查询 W25Qxx_CMD_ReadStatus_REG1 寄存器，将读取到的状态字节中的 W25Qxx_Status_REG1_BUSY 不停的与0作比较
// 读状态寄存器1的第0位（只读），Busy标志位，当正在擦除/写入数据/写命令时会被置1，空闲或通信结束为0
	
	s_config.Match           = 0;   									//	匹配值
	s_config.MatchMode       = QSPI_MATCH_MODE_AND;	      	//	与运算
	s_config.Interval        = 0x10;	                     	//	轮询间隔
	s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;	// 自动停止模式
	s_config.StatusBytesSize = 1;	                        	//	状态字节数
	s_config.Mask            = W25Qxx_Status_REG1_BUSY;	   // 对在轮询模式下接收的状态字节进行屏蔽，只比较需要用到的位
		
	// 发送轮询等待命令
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // 轮询等待无响应
	}
	return QSPI_W25Qxx_OK; // 通信正常结束

}

int8_t QSPI_W25Qxx_SectorErase(uint32_t SectorAddress)	
{
	QSPI_CommandTypeDef s_command;	// QSPI传输配置
	
	s_command.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;    // 1线指令模式
	s_command.AddressSize       	= QSPI_ADDRESS_24_BITS;       // 24位地址模式
	s_command.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;  //	无交替字节 
	s_command.DdrMode           	= QSPI_DDR_MODE_DISABLE;      // 禁止DDR模式
	s_command.DdrHoldHalfCycle  	= QSPI_DDR_HHC_ANALOG_DELAY;  // DDR模式中数据延迟，这里用不到
	s_command.SIOOMode          	= QSPI_SIOO_INST_EVERY_CMD;	// 每次传输数据都发送指令
	s_command.AddressMode 			= QSPI_ADDRESS_1_LINE;        // 1线地址模式
	s_command.DataMode 				= QSPI_DATA_NONE;             // 无数据
	s_command.DummyCycles 			= 0;                          // 空周期个数
	s_command.Address           	= SectorAddress;              // 要擦除的地址
	s_command.Instruction	 		= W25Qxx_CMD_SectorErase;     // 扇区擦除命令

	// 发送写使能
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable;		// 写使能失败
	}
	// 发出擦除命令
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase;				// 擦除失败
	}
	// 使用自动轮询标志位，等待擦除的结束 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING;		// 轮询等待无响应
	}
	return QSPI_W25Qxx_OK; // 擦除成功
}

int8_t QSPI_W25Qxx_BlockErase_32K (uint32_t SectorAddress)	
{
	QSPI_CommandTypeDef s_command;	// QSPI传输配置
	
	s_command.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;    // 1线指令模式
	s_command.AddressSize       	= QSPI_ADDRESS_24_BITS;       // 24位地址模式
	s_command.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;  //	无交替字节 
	s_command.DdrMode           	= QSPI_DDR_MODE_DISABLE;      // 禁止DDR模式
	s_command.DdrHoldHalfCycle  	= QSPI_DDR_HHC_ANALOG_DELAY;  // DDR模式中数据延迟，这里用不到
	s_command.SIOOMode          	= QSPI_SIOO_INST_EVERY_CMD;	// 每次传输数据都发送指令
	s_command.AddressMode 			= QSPI_ADDRESS_1_LINE;        // 1线地址模式
	s_command.DataMode 				= QSPI_DATA_NONE;             // 无数据
	s_command.DummyCycles 			= 0;                          // 空周期个数
	s_command.Address           	= SectorAddress;              // 要擦除的地址
	s_command.Instruction	 		= W25Qxx_CMD_BlockErase_32K;  // 块擦除命令，每次擦除32K字节

	// 发送写使能	
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable;		// 写使能失败
	}
	// 发出擦除命令
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase;				// 擦除失败
	}
	// 使用自动轮询标志位，等待擦除的结束 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING;		// 轮询等待无响应
	}
	return QSPI_W25Qxx_OK;	// 擦除成功
}

int8_t QSPI_W25Qxx_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	QSPI_CommandTypeDef s_command;	// QSPI传输配置	
	
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    		// 1线指令模式
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;            // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  		// 无交替字节 
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;     		// 禁止DDR模式
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY; 		// DDR模式中数据延迟，这里用不到
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;			// 每次传输数据都发送指令	
	s_command.AddressMode 		 = QSPI_ADDRESS_1_LINE; 				// 1线地址模式
	s_command.DataMode    		 = QSPI_DATA_4_LINES;    				// 4线数据模式
	s_command.DummyCycles 		 = 0;                    				// 空周期个数
	s_command.NbData      		 = NumByteToWrite;      			   // 数据长度，最大只能256字节
	s_command.Address     		 = WriteAddr;         					// 要写入 W25Qxx 的地址
	s_command.Instruction 		 = W25Qxx_CMD_QuadInputPageProgram; // 1-1-4模式下(1线指令1线地址4线数据)，页编程指令
	
	// 写使能
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable;	// 写使能失败
	}
	// 写命令
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT;		// 传输数据错误
	}
	// 开始传输数据
	if (HAL_QSPI_Transmit(&hqspi, pBuffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT;		// 传输数据错误
	}
	// 使用自动轮询标志位，等待写入的结束 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // 轮询等待无响应
	}
	return QSPI_W25Qxx_OK;	// 写数据成功
}

int8_t QSPI_W25Qxx_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size)
{	
	uint32_t end_addr, current_size, current_addr;
	uint8_t *write_data;  // 要写入的数据

	current_size = W25Qxx_PageSize - (WriteAddr % W25Qxx_PageSize); // 计算当前页还剩余的空间

	if (current_size > Size)	// 判断当前页剩余的空间是否足够写入所有数据
	{
		current_size = Size;		// 如果足够，则直接获取当前长度
	}

	current_addr = WriteAddr;		// 获取要写入的地址
	end_addr = WriteAddr + Size;	// 计算结束地址
	write_data = pBuffer;			// 获取要写入的数据

	do
	{
		// 发送写使能
		if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
		{
			return W25Qxx_ERROR_WriteEnable;
		}

		// 按页写入数据
		else if(QSPI_W25Qxx_WritePage(write_data, current_addr, current_size) != QSPI_W25Qxx_OK)
		{
			return W25Qxx_ERROR_TRANSMIT;
		}

		// 使用自动轮询标志位，等待写入的结束 
		else 	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
		{
			return W25Qxx_ERROR_AUTOPOLLING;
		}

		else // 按页写入数据成功，进行下一次写数据的准备工作
		{
			current_addr += current_size;	// 计算下一次要写入的地址
			write_data += current_size;	// 获取下一次要写入的数据存储区地址
			// 计算下一次写数据的长度
			current_size = ((current_addr + W25Qxx_PageSize) > end_addr) ? (end_addr - current_addr) : W25Qxx_PageSize;
		}
	}
	while (current_addr < end_addr) ; // 判断数据是否全部写入完毕

	return QSPI_W25Qxx_OK;	// 写入数据成功

}

/**********************************************************************************************************************************
*
*	函 数 名: QSPI_W25Qxx_ReadBuffer
*
*	入口参数: pBuffer 		 - 要读取的数据
*				 ReadAddr 		 - 要读取 W25Qxx 的地址
*				 NumByteToRead  - 数据长度，最大不能超过flash芯片的大小
*
*	返 回 值: QSPI_W25Qxx_OK 		     - 读数据成功
*				 W25Qxx_ERROR_TRANSMIT	  - 传输失败
*				 W25Qxx_ERROR_AUTOPOLLING - 轮询等待无响应
*
*	函数功能: 读取数据，最大不能超过flash芯片的大小
*
*	说    明: 1.Flash的读取速度取决于QSPI的通信时钟，最大不能超过133M
*				 2.这里使用的是1-4-4模式下(1线指令4线地址4线数据)，快速读取指令 Fast Read Quad I/O
*				 3.使用快速读取指令是有空周期的，具体参考W25Q64JV的手册  Fast Read Quad I/O  （0xEB）指令
*				 4.实际使用中，是否使用DMA、编译器的优化等级以及数据存储区的位置(内部 TCM SRAM 或者 AXI SRAM)都会影响读取的速度
*			    5.在本例程中，使用的是库函数进行直接读写，keil版本5.30，编译器AC6.14，编译等级Oz image size，读取速度为 7M字节/S ，
*		         数据放在 TCM SRAM 或者 AXI SRAM 都是差不多的结果
*		       6.因为CPU直接访问外设寄存器的效率很低，直接使用HAL库进行读写的话，速度很慢，使用MDMA进行读取，可以达到 58M字节/S
*	          7. W25Q64JV 所允许的最高驱动频率为133MHz，750的QSPI最高驱动频率也是133MHz ，但是对于HAL库函数直接读取而言，
*		          驱动时钟超过15M已经不会对性能有提升，对速度要求高的场合可以用MDMA的方式
*
*****************************************************************************************************************FANKE************/


int8_t QSPI_W25Qxx_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	QSPI_CommandTypeDef s_command;	// QSPI传输配置
	
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    		// 1线指令模式
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;            // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
	s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	s_command.AlternateBytes   = 0xF0;	
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;     		// 禁止DDR模式
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY; 		// DDR模式中数据延迟，这里用不到
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;			// 每次传输数据都发送指令	
	s_command.AddressMode 		 = QSPI_ADDRESS_4_LINES; 				// 4线地址模式
	s_command.DataMode    		 = QSPI_DATA_4_LINES;    				// 4线数据模式
	s_command.DummyCycles 		 = 4;                    				// 空周期个数
	s_command.NbData      		 = NumByteToRead;      			   	// 数据长度，最大不能超过flash芯片的大小
	s_command.Address     		 = ReadAddr;         					// 要读取 W25Qxx 的地址
	s_command.Instruction 		 = W25Qxx_CMD_FastReadQuad_IO; 		// 1-4-4模式下(1线指令4线地址4线数据)，快速读取指令
	
	// 发送读取命令
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT;		// 传输数据错误
	}

	//	接收数据
	
	if (HAL_QSPI_Receive(&hqspi, pBuffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT;		// 传输数据错误
	}

	// 使用自动轮询标志位，等待接收的结束 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // 轮询等待无响应
	}
	return QSPI_W25Qxx_OK;	// 读取数据成功
}

int8_t QSPI_W25Qxx_Reset(void)	
{
	QSPI_CommandTypeDef s_command;	// QSPI传输配置

	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;   	// 1线指令模式
	s_command.AddressMode 		 = QSPI_ADDRESS_NONE;   			// 无地址模式
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; 	// 无交替字节 
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;     	// 禁止DDR模式
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY; 	// DDR模式中数据延迟，这里用不到
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;	 	// 每次传输数据都发送指令
	s_command.DataMode 			 = QSPI_DATA_NONE;       			// 无数据模式	
	s_command.DummyCycles 		 = 0;                     			// 空周期个数
	s_command.Instruction 		 = W25Qxx_CMD_EnableReset;       // 执行复位使能命令

	// 发送复位使能命令
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) 
	{
		return W25Qxx_ERROR_INIT;			// 如果发送失败，返回错误信息
	}
	// 使用自动轮询标志位，等待通信结束
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING;	// 轮询等待无响应
	}

	s_command.Instruction  = W25Qxx_CMD_ResetDevice;     // 复位器件命令    

	//发送复位器件命令
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) 
	{
		return W25Qxx_ERROR_INIT;		  // 如果发送失败，返回错误信息
	}
	// 使用自动轮询标志位，等待通信结束
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING;	// 轮询等待无响应
	}	
	return QSPI_W25Qxx_OK;	// 复位成功
}

uint32_t QSPI_W25Qxx_ReadID(void)	
{
	QSPI_CommandTypeDef s_command;	// QSPI传输配置
	uint8_t	QSPI_ReceiveBuff[3];		// 存储QSPI读到的数据
	uint32_t	W25Qxx_ID;					// 器件的ID

	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    // 1线指令模式
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;     	 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  // 无交替字节 
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;      // 禁止DDR模式
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  // DDR模式中数据延迟，这里用不到
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;	 // 每次传输数据都发送指令
	s_command.AddressMode		 = QSPI_ADDRESS_NONE;   		 // 无地址模式
	s_command.DataMode			 = QSPI_DATA_1_LINE;       	 // 1线数据模式
	s_command.DummyCycles 		 = 0;                   		 // 空周期个数
	s_command.NbData 				 = 3;                          // 传输数据的长度
	s_command.Instruction 		 = W25Qxx_CMD_JedecID;         // 执行读器件ID命令

	// 发送指令
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) 
	{
//		return W25Qxx_ERROR_INIT;		// 如果发送失败，返回错误信息
	}
	// 接收数据
	if (HAL_QSPI_Receive(&hqspi, QSPI_ReceiveBuff, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) 
	{
//		return W25Qxx_ERROR_TRANSMIT;  // 如果接收失败，返回错误信息
	}
	// 将得到的数据组合成ID
	W25Qxx_ID = (QSPI_ReceiveBuff[0] << 16) | (QSPI_ReceiveBuff[1] << 8 ) | QSPI_ReceiveBuff[2];

	return W25Qxx_ID; // 返回ID
}

#define W25Qxx_NumByteToTest   	16*1024					// 测试数据的长度，64K
int32_t QSPI_Status ; 		 //检测标志位
uint32_t W25Qxx_TestAddr  =	0	;							// 测试地址
uint8_t  W25Qxx_WriteBuffer[W25Qxx_NumByteToTest];		//	写数据数组
uint8_t  W25Qxx_ReadBuffer[W25Qxx_NumByteToTest];		//	读数据数组

int8_t QSPI_W25Qxx_Test(void)		//Flash读写测试
{
	uint32_t	Device_ID;	// 器件ID
	Device_ID = QSPI_W25Qxx_ReadID(); 		// 读取器件ID
	debug_tx5 ("W25Q64 OK,flash ID:0x%x\r\n",Device_ID);		// 初始化成功


	
	uint32_t i = 0;	// 计数变量
	uint32_t ExecutionTime_Begin;		// 开始时间
	uint32_t ExecutionTime_End;		// 结束时间
	uint32_t ExecutionTime;				// 执行时间	
	float    ExecutionSpeed;			// 执行速度

// 擦除 >>>>>>>    
	
	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	QSPI_Status 			= QSPI_W25Qxx_BlockErase_32K(W25Qxx_TestAddr);	// 擦除32K字节
	ExecutionTime_End		= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin; // 计算擦除时间，单位ms
	
	if( QSPI_Status == QSPI_W25Qxx_OK )
	{
		debug_tx5 ("\r\n1.W25Q64 BlockErase succuess, time: %d ms\r\n",ExecutionTime);		
	}
	else
	{
		debug_tx5 ("\r\n 1.Erase Failed!!!!!  %d\r\n",QSPI_Status);
		while (1);
	}	
	
// 写入 >>>>>>>    

	for(i=0;i<W25Qxx_NumByteToTest;i++)  //先将数据写入数组
	{
		W25Qxx_WriteBuffer[i] = i;
	}
	debug_tx5 ("\r\n Weite buf0,255 = %d,%d\r\n",W25Qxx_WriteBuffer[0],W25Qxx_WriteBuffer[255]);
	
	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	QSPI_Status				= QSPI_W25Qxx_WriteBuffer(W25Qxx_WriteBuffer,W25Qxx_TestAddr,W25Qxx_NumByteToTest); // 写入数据
	ExecutionTime_End		= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	
	ExecutionTime  = ExecutionTime_End - ExecutionTime_Begin; 		// 计算擦除时间，单位ms
	ExecutionSpeed = (float)W25Qxx_NumByteToTest / ExecutionTime ; // 计算写入速度，单位 KB/S

	if( QSPI_Status == QSPI_W25Qxx_OK )
	{
		debug_tx5 ("\r\n2.Write OK,Size:%d KB, Time:%d ms, Write Speed:%.2f KB/s\r\n",W25Qxx_NumByteToTest/1024,ExecutionTime,ExecutionSpeed);		
	}
	else
	{
		debug_tx5 ("\r\n2.Write Failed!!!!!  %d\r\n",QSPI_Status);
		while (1);
	}		
	
// 读取 >>>>>>>    
	
	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms	
	QSPI_Status				= QSPI_W25Qxx_ReadBuffer(W25Qxx_ReadBuffer,W25Qxx_TestAddr,W25Qxx_NumByteToTest);	// 读取数据
	ExecutionTime_End		= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	
	ExecutionTime  = ExecutionTime_End - ExecutionTime_Begin; 					// 计算擦除时间，单位ms
	ExecutionSpeed = (float)W25Qxx_NumByteToTest / ExecutionTime / 1024 ; 	// 计算读取速度，单位 MB/S 

	debug_tx5 ("\r\n Read buf[0,255] = [%d,%d]\r\n",W25Qxx_ReadBuffer[0],W25Qxx_ReadBuffer[255]);
	
	if( QSPI_Status == QSPI_W25Qxx_OK )
	{
		debug_tx5 ("\r\n3.Raed OK,Size:%d KB, Time:%d ms, Read Speed:%.2f MB/s \r\n",W25Qxx_NumByteToTest/1024,ExecutionTime,ExecutionSpeed);		
	}
	else
	{
		debug_tx5 ("\r\n3.Raed Worng!:%d\r\n",QSPI_Status);
		while (1);
	}			
	
// 数据校验 >>>>>>>    

	
	for(i=0;i<W25Qxx_NumByteToTest;i++)	//验证读出的数据是否等于写入的数据
	{
		if( W25Qxx_WriteBuffer[i] != W25Qxx_ReadBuffer[i] )	//如果数据不相等，则返回0	
		{
			debug_tx5 ("\r\n4.Check Failed!!!!!\r\n");	
			
			while(1);
		}
	}			
	debug_tx5 ("\r\nnCheck OK!!!!! OK\r\n");		
	
	
// 读取整片Flash的数据，用以测试速度 >>>>>>>  	
	
	debug_tx5 ("\r\n*****************************************************************************************************\r\n");		
//	debug_tx5 ("\r\n上面的测试中，读取的数据比较小，耗时很短，加之测量的最小单位为ms，计算出的读取速度误差较大\r\n");		
//	debug_tx5 ("\r\n接下来读取整片flash的数据用以测试速度，这样得出的速度误差比较小\r\n");		
	debug_tx5 ("\r\nStart Read>>>>\r\n");		
	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms		
	
	for(i=0;i<W25Qxx_FlashSize/(W25Qxx_NumByteToTest);i++)	// 每次读取 W25Qxx_NumByteToTest 字节的数据
	{
		QSPI_Status		 = QSPI_W25Qxx_ReadBuffer(W25Qxx_ReadBuffer,W25Qxx_TestAddr,W25Qxx_NumByteToTest);
		W25Qxx_TestAddr = W25Qxx_TestAddr + W25Qxx_NumByteToTest;		
	}
	ExecutionTime_End		= HAL_GetTick();	// 获取 systick 当前时间，单位ms
	
	ExecutionTime  = ExecutionTime_End - ExecutionTime_Begin; 					// 计算擦除时间，单位ms
	ExecutionSpeed = (float)W25Qxx_FlashSize / ExecutionTime / 1024 ; 	// 计算读取速度，单位 MB/S 

	if( QSPI_Status == QSPI_W25Qxx_OK )
	{
		debug_tx5 ("\r\n Read OK ,Size:%d MB, 耗时: %d ms, 读取速度：%.2f MB/s \r\n",W25Qxx_FlashSize/1024/1024,ExecutionTime,ExecutionSpeed);		
	}
	else
	{
		debug_tx5 ("\r\n读取错误!!!!!  错误代码:%d\r\n",QSPI_Status);
		while (1);
	}	
	
	return QSPI_W25Qxx_OK ;  // 测试通过	
}
 

#endif
