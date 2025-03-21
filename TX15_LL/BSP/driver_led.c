
#include "driver_led.h"

#include "hal.h"

void ledInit(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOI);
		  /**/
  LL_GPIO_ResetOutputPin(GPIOI, LED_RED_GPIO_PIN|LED_BLUE_GPIO_PIN|LED_GREEN_GPIO_PIN);
	GPIO_InitStruct.Pin = LED_RED_GPIO_PIN|LED_BLUE_GPIO_PIN|LED_GREEN_GPIO_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOI, &GPIO_InitStruct);
	
}

void ledOff(void)
{

  GPIO_LED_GPIO_OFF(LED_RED_GPIO,LED_RED_GPIO_PIN);


  GPIO_LED_GPIO_OFF(LED_BLUE_GPIO,LED_BLUE_GPIO_PIN);


  GPIO_LED_GPIO_OFF(LED_GREEN_GPIO,LED_GREEN_GPIO_PIN);

}

void ledRed(void)
{
  GPIO_LED_GPIO_ON(LED_RED_GPIO,LED_RED_GPIO_PIN);
}

void ledGreen(void)
{
  GPIO_LED_GPIO_ON(LED_GREEN_GPIO,LED_GREEN_GPIO_PIN);

}

void ledBlue(void)
{
  GPIO_LED_GPIO_ON(LED_BLUE_GPIO,LED_BLUE_GPIO_PIN);

}
