#include "board.h"
void board_init(void)
{
  HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, GPIO_PIN_SET);
  // TFT_init();
	// MX_LTDC_Init();
	// MX_DMA2D_Init();
  // ltdc_clear(WHITE);
}