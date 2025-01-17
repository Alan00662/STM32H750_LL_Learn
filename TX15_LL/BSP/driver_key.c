
#include "driver_key.h"
#include "hal.h"
void keysInit(void) 
{ 
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
	  /**/
  GPIO_InitStruct.Pin = KEYS_GPIO_PIN_PAGEUP|KEYS_GPIO_PIN_ENTER|
													KEYS_GPIO_PIN_EXIT|KEYS_GPIO_PIN_TELE;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = KEYS_GPIO_PIN_MDL;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(KEYS_GPIO_REG_MDL, &GPIO_InitStruct);
	
	  /**/
  GPIO_InitStruct.Pin = KEYS_GPIO_PIN_PAGEDN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = KEYS_GPIO_PIN_SYS;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(KEYS_GPIO_REG_SYS, &GPIO_InitStruct);
	
}

key_info_t Key;

uint8_t readKeys(EnumKeys key)
{
	uint8_t key_buf[MAX_KEYS]={0};
	key_buf[KEY_EXIT]= LL_GPIO_IsOutputPinSet(KEYS_GPIO_REG_EXIT,KEYS_GPIO_PIN_EXIT);
	key_buf[KEY_ENTER]= LL_GPIO_IsOutputPinSet(KEYS_GPIO_REG_ENTER,KEYS_GPIO_PIN_ENTER);
	key_buf[KEY_PAGEUP]= LL_GPIO_IsOutputPinSet(KEYS_GPIO_REG_PAGEUP,KEYS_GPIO_PIN_PAGEUP);
	key_buf[KEY_PAGEDN]= LL_GPIO_IsOutputPinSet(KEYS_GPIO_REG_PAGEDN,KEYS_GPIO_PIN_PAGEDN);
	key_buf[KEY_MODEL]= LL_GPIO_IsOutputPinSet(KEYS_GPIO_REG_MDL,KEYS_GPIO_PIN_MDL);
	key_buf[KEY_TELE]= LL_GPIO_IsOutputPinSet(KEYS_GPIO_REG_TELE,KEYS_GPIO_PIN_TELE);
	key_buf[KEY_SYS]= LL_GPIO_IsOutputPinSet(KEYS_GPIO_REG_SYS,KEYS_GPIO_PIN_SYS);
	return key_buf[key];
	
}

enum PhysicalTrims {
  TR3L = 0,
  TR3R,
  TR1D = 2,
  TR1U,
  TR2D = 4,
  TR2U,
  TR4L = 6,
  TR4R
};

uint32_t readTrims()
{
}
