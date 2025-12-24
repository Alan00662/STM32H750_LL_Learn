
#include "bsp_lcd_gpio.h"
#include "quadspi.h"

QSPI_HandleTypeDef qspi_tft;

void TFT_GPIO_init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  
#if BackLight_USE_PWM == 0 
  GPIO_InitStruct.Pin = TFT_BL_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(TFT_BL_GPIO_PORT, &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_SET);
  
#endif

#if !USE_LCD_SPI_PIN == 1

	GPIO_InitStruct.Pin = TFT_CLK_GPIO_PIN|TFT_MOSI_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
#else 

	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
  

#endif

	GPIO_InitStruct.Pin = TFT_RESET_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(TFT_RESET_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = TFT_CS_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(TFT_CS_GPIO_PORT, &GPIO_InitStruct);
  
#if USE_LTDC_PIN_TEST
	GPIO_InitStruct.Pin = GPIO_PIN_14;    //LTDC！！CLK
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_7;    //LTDC！！CLK
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);
	
#endif
}



