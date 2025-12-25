#ifndef __HAL_H__
#define __HAL_H__

#define BackLight_USE_PWM 	0
#define LCD_DIR				1

#define USE_SDRAM			0
#define TEST_SDRAM_DMA2D	0
#define Brush_Screen_Test	0

#define UART4_USE_FIFO		1
#define Motor_USE_PWM		1

#define Touch_Test			0

#define USE_Fire_GT911		1
#define USE_SOFT_GT911		0
#define USE_TEST_GT911		0
#define USE_Android_GT911	0
#define DFSDM_TEST				0
#define USE_TAS2505_TEST	0
#define USE_FATFS_Player	1
/*GT911配置更新*/
#define UPDATE_CONFIG		0    // 1 ：更新配置    0 ：不更新配置

#define USE_QSPI_TEST1		1
#define USE_QSPI_TEST2		0

#define Dashed_Line			1
#define USE_LED_TEST		0

#define USE_LCD_SPI_PIN		1
#define USE_LTDC_PIN_TEST 0

#endif /* __HAL_H__ */