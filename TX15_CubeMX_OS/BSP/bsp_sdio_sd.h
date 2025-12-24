#ifndef __STM324x9I_EVAL_SDIO_SD_H
#define __STM324x9I_EVAL_SDIO_SD_H

#include "stm32h7xx.h"
//等待时间

//耳机接口检测GPIO
#define SD_DET_GPIO_PORT            GPIOH
#define SD_DET_GPIO_PIN             GPIO_PIN_8
#define SD_DET_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOH_CLK_ENABLE(); } while(0)

#define      SD_PRESENT        			HAL_GPIO_ReadPin(SD_DET_GPIO_PORT, SD_DET_GPIO_PIN)


#define SD_TIMEOUT             ((uint32_t)0x00000100U)
//块的大小（以字节为单位）//8192
#define BLOCK_SIZE            512 
//块的数目
#define NUMBER_OF_BLOCKS      10
//块的数据大小
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)

HAL_StatusTypeDef BSP_SD_Init(void);
static void BSP_SD_MspInit(void);
//static HAL_StatusTypeDef BSP_SD_Init(void);
static void SD_EraseTest(void);
static HAL_StatusTypeDef Wait_SDCARD_Ready(void);
static HAL_StatusTypeDef Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);

void sd_conect_gpio_init(void);
void SD_Test(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
#endif 
/************************END OF FILE*******************/
