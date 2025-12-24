/**
  ******************************************************************************
  * @file    bsp_sdio_sd.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   SDIO sd卡测试驱动（不含文件系统）
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 H750 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "bsp_sdio_sd.h"
#include "main.h"   
#include "delay.h" 
#include "usart.h"


SD_HandleTypeDef uSdHandle;


//SDMMC只能访问AXI_SRAM
uint8_t Buffer_Block_Tx[MULTI_BUFFER_SIZE/4];
uint8_t Buffer_Block_Rx[MULTI_BUFFER_SIZE/4];

//发送标志位
__IO uint8_t TX_Flag=0;
//接受标志位
__IO uint8_t RX_Flag=0; 
/**
  * @brief  SD_Card测试函数
  * @param  无
  * @retval 无
  */
void SD_Test(void)
{

    /*------------------------------ SD 初始化 ------------------------------ */
    if(BSP_SD_Init() != HAL_OK)
    {    

        debug_tx5("SD卡初始化失败，请确保SD卡已正确接入开发板，或换一张SD卡测试！\n");
    }
    else
    {
        debug_tx5("SD卡初始化成功！\n");	     

        /*擦除测试*/
        SD_EraseTest();
		
		debug_tx5("single block 读写测试。。。\n");

        /*single block 读写测试*/
        SD_SingleBlockTest();



        /*muti block 读写测试*/
        SD_MultiBlockTest();
	
    } 
} 

void sd_conect_gpio_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

	SD_DET_GPIO_CLK_ENABLE();

    /*Configure GPIO pins : PIPin PIPin PIPin */
    GPIO_InitStruct.Pin = SD_DET_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SD_DET_GPIO_PORT, &GPIO_InitStruct);

}

/**
  * @brief  初始化SDMMC1及SD卡
  * @param  无
  * @retval HAL_OK：初始化成功；HAL_ERROR：初始化失败
  */
HAL_StatusTypeDef BSP_SD_Init(void)
{ 
    HAL_StatusTypeDef sd_state = HAL_OK;
    
    /* 定义SDMMC句柄 */
    uSdHandle.Instance = SDMMC2;
    /* 上升沿有效 */
    uSdHandle.Init.ClockEdge           = SDMMC_CLOCK_EDGE_RISING;
    /* 关闭节能模式 */
    uSdHandle.Init.ClockPowerSave      = SDMMC_CLOCK_POWER_SAVE_DISABLE;
    /* 总线宽度为4 */
    uSdHandle.Init.BusWide             = SDMMC_BUS_WIDE_4B;
    /* 关闭硬件流控制 */
    uSdHandle.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
    /* 时钟分频因子为0 */
    uSdHandle.Init.ClockDiv            = 10;
    
    /* 初始化SD底层驱动 */
    BSP_SD_MspInit();

    /* HAL SD 初始化 */
    if(HAL_SD_Init(&uSdHandle) != HAL_OK)
    {
      sd_state = HAL_ERROR;
    }
    
    /* 配置SD总线位宽 */
    if(sd_state == HAL_OK)
    {
      /* 配置为4bit模式 */
      if(HAL_SD_ConfigWideBusOperation(&uSdHandle, uSdHandle.Init.BusWide) != HAL_OK)
      {
        sd_state = HAL_ERROR;
      }
      else
      {
        sd_state = HAL_OK;
      }
    }
    
  return  sd_state;
}
/**
  * @brief  SD卡擦除测试
  * @param  无
  * @retval 无
  */
static void SD_EraseTest(void)
{
    HAL_StatusTypeDef Status = HAL_OK;
    HAL_StatusTypeDef EraseStatus = HAL_OK;
    if (Status == HAL_OK)
    {
        Status = HAL_SD_Erase(&uSdHandle, 0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
        //等待擦除完成
        if(Wait_SDCARD_Ready() != HAL_OK)
        {
            EraseStatus = HAL_ERROR;
        }
    }     
    if(EraseStatus == HAL_OK)
    {    

      debug_tx5("SD卡擦除测试成功！\n");
    }
    else
    {

      debug_tx5("SD卡擦除测试失败！\n");
      debug_tx5("温馨提示：部分SD卡不支持擦除测试，若SD卡能通过下面的single读写测试，即表示SD卡能够正常使用。\n");
    }    
}

/**
  * @brief  SD卡单块读写测试
  * @param  无
  * @retval 无
  */
void SD_SingleBlockTest(void)
{
    HAL_StatusTypeDef Status =  HAL_OK;
    HAL_StatusTypeDef TransferStatus1 = HAL_ERROR;
    /* Fill the buffer to send */
    Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE/4, 0);    
//    SCB_CleanDCache_by_Addr((uint32_t*)Buffer_Block_Tx, BLOCK_SIZE/4);
    if(Status == HAL_OK)
    {
        /* 起始地址为0，写入512个字节的内容 */
        Status = HAL_SD_WriteBlocks(&uSdHandle, Buffer_Block_Tx, 0x00,1,1000);
        while(TX_Flag == 0);
        debug_tx5("ok,Status = %d\n",Status);
	}
	else
	{
		 debug_tx5("failed,Status1 = %d\n",Status);
	}	
    /* Fill the buffer to reception */
    Fill_Buffer(Buffer_Block_Rx, BLOCK_SIZE/4, 0);   
//    SCB_CleanDCache_by_Addr((uint32_t*)Buffer_Block_Rx, BLOCK_SIZE/4); 
    if(Status == HAL_OK)
    {
        /* 起始地址为0，读取512个字节的内容  */
        Status = HAL_SD_ReadBlocks(&uSdHandle, Buffer_Block_Rx,0, 1,1000);
        while(RX_Flag == 0);
    }
	else
	{
		 debug_tx5("failed,Status2 = %d\n",Status);
	}    
    if (Status == HAL_OK)
    {
        TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE/4);
    }
	else
	{
		debug_tx5("failed,Status3 = %d\n",Status);
	}
	
    if(TransferStatus1 == HAL_OK)
    {

        debug_tx5("Single block 测试成功！\n");
    }
    else
    {

        debug_tx5("Single block 测试失败，请确保SD卡正确接入开发板，或换一张SD卡测试！\n");
    }
}
/**
  * @brief  SD卡多块读写测试
  * @param  无
  * @retval 无
  */
void SD_MultiBlockTest(void)
{ 
    HAL_StatusTypeDef Status =  HAL_OK;
    HAL_StatusTypeDef TransferStatus1 = HAL_ERROR;
    TX_Flag = 0;
    RX_Flag = 0; 
    /* Fill the buffer to send */
    Fill_Buffer(Buffer_Block_Tx, MULTI_BUFFER_SIZE/4, 0);    
//    SCB_CleanDCache_by_Addr((uint32_t*)Buffer_Block_Tx, MULTI_BUFFER_SIZE/4);
    if(Status == HAL_OK)
    {
        /* 起始地址为0，写入NUMBER_OF_BLOCKS*512个字节的内容  */
        Status = HAL_SD_WriteBlocks(&uSdHandle, (uint8_t *)Buffer_Block_Tx, 0,NUMBER_OF_BLOCKS,1000);
		HAL_Delay(10);
        while(TX_Flag == 0);
    } 
    /* Fill the buffer to reception */
    Fill_Buffer(Buffer_Block_Rx, MULTI_BUFFER_SIZE/4, 0);   
//    SCB_CleanDCache_by_Addr((uint32_t*)Buffer_Block_Rx, MULTI_BUFFER_SIZE/4); 
    if(Status == HAL_OK)
    {
        /* 起始地址为0，读取NUMBER_OF_BLOCKS*512个字节的内容  */
         Status = HAL_SD_ReadBlocks(&uSdHandle, Buffer_Block_Rx,0, NUMBER_OF_BLOCKS,1000);
				  HAL_Delay(10);
        //等待DMA传输完成
        while(RX_Flag == 0);
    }    
    if (Status == HAL_OK)
    {
        TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, MULTI_BUFFER_SIZE/4);
    }
    if(TransferStatus1 == HAL_OK)
    {

        debug_tx5("Multi block 测试成功！\n");
    }
    else
    {

        debug_tx5("Multi block 测试失败，请确保SD卡正确接入开发板，或换一张SD卡测试！\n");
    }
}

/**
  * @brief  SD卡等待擦除完成函数
  * @param  无
  * @retval HAL_OK：擦除成功；HAL_ERROR：擦除失败
  */
static HAL_StatusTypeDef Wait_SDCARD_Ready(void)
{
    uint32_t loop = SD_TIMEOUT;
    
    /* Wait for the Erasing process is completed */
    /* Verify that SD card is ready to use after the Erase */
    while(loop > 0)
    {
      loop--;
      if(HAL_SD_GetCardState(&uSdHandle) == HAL_SD_CARD_TRANSFER)
      {
          return HAL_OK;
      }
    }
    return HAL_ERROR;
}
/**
  * @brief  数组匹配检测函数
  * @param  pBuffer1：发送数组；pBuffer2：接受数组；BufferLength：数组长度
  * @retval HAL_OK：匹配；HAL_ERROR：不匹配
  */
static HAL_StatusTypeDef Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
    while (BufferLength--)
    {
      if (*pBuffer1 != *pBuffer2)
      {      
        return HAL_ERROR;      
      }
      else{

        pBuffer1++;
        pBuffer2++;
      }
    }
    return HAL_OK;
}


/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  * @retval None
  */
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset)
{
  uint32_t index = 0;
  /* Put in global buffer same values */
  for (index = 0; index < BufferLength; index++)
  {
    pBuffer[index] = index + Offset;
	  debug_tx5("pBuffer[%d]",index);
  }
  debug_tx5("Fill_Buffer ok ");
}

/**
  * @brief  初始化SD外设
  * @param  无
  * @param  无
  * @retval None
  */
static void BSP_SD_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

	  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /* USER CODE BEGIN SDMMC2_MspInit 0 */

  /* USER CODE END SDMMC2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC;
    PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* SDMMC2 clock enable */
    __HAL_RCC_SDMMC2_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**SDMMC2 GPIO Configuration
    PB4 (NJTRST)     ------> SDMMC2_D3
    PG11     ------> SDMMC2_D2
    PD6     ------> SDMMC2_CK
    PD7     ------> SDMMC2_CMD
    PB15     ------> SDMMC2_D1
    PB14     ------> SDMMC2_D0
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_15|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_SDIO2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_SDIO2;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_SDIO2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(SDMMC2_IRQn,0,0);  //配置SDMMC2中断
    HAL_NVIC_EnableIRQ(SDMMC2_IRQn);        //使能SDMMC2中断

//    /* 使能 SDMMC 时钟 */
//    __HAL_RCC_SDMMC1_CLK_ENABLE();
//  
//    /* 使能 GPIOs 时钟 */
//    __HAL_RCC_GPIOC_CLK_ENABLE();
//    __HAL_RCC_GPIOD_CLK_ENABLE();
//  
//    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
//                          |GPIO_PIN_12;
//    /*设置引脚的输出类型为推挽输出*/
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    /*设置引脚为不需要上、下拉模式*/  
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    /*设置引脚速率为高速 */      
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    /*设置为SDIO1复用 */  
//    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
//    /*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/  
//    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

//    GPIO_InitStruct.Pin = GPIO_PIN_2;
//    /*设置引脚的输出类型为推挽输出*/    
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    /*设置引脚为不需要上、下拉模式*/  
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    /*设置引脚速率为高速 */ 
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    /*设置为SDIO1复用 */  
//    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
//    /*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/ 
//    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

//        
    HAL_NVIC_SetPriority(SDMMC2_IRQn,0,0);  //配置SDMMC1中断
    HAL_NVIC_EnableIRQ(SDMMC2_IRQn);        //使能SDMMC1中断
	HAL_NVIC_SetPriority(SysTick_IRQn, 0x0E ,0);
}

//SDMMC1发送完成回调函数
void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
    TX_Flag=1; //标记写完成
}

//SDMMC1接受完成回调函数
void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
    //SCB_InvalidateDCache_by_Addr((uint32_t*)Buffer_Block_Rx, MULTI_BUFFER_SIZE/4);
    RX_Flag=1;
}

/************************END OF FILE*******************/
