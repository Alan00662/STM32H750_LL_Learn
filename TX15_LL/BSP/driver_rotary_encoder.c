
#include "driver_rotary_encoder.h"
#include "tim.h"
#include "hal.h"
#include "driver_key.h"

#define ON_DETENT(p) ((p == 3) || (p == 0))

volatile uint32_t rotencValue = 0;
volatile uint32_t rotencDt = 0;

// Last encoder pins state
static uint8_t lastPins = 0;
// Record encoder position change between detents
int8_t reChgPos = 0;
// Used on start to ignore movement until encoder position on detent
_Bool skipUntilDetent = 0;

int32_t rotaryEncoderGetValue()
{
  return rotencValue;
}

void rotaryEncoderCheck(void)
{
  // Value increment for each state transition of the RE pins
#if defined(ROTARY_ENCODER_INVERTED)
  static int8_t reInc[4][4] = {
    // Prev = 0
    {  0, -1,  1, -2 },
    // Prev = 1
    {  1,  0,  0, -1 },
    // Prev = 2
    { -1,  0,  0,  1 },
    // Prev = 3
    {  2,  1, -1,  0 },
  };
#else
  static int8_t reInc[4][4] = {
    // Prev = 0
    {  0,  1, -1,  2 },
    // Prev = 1
    { -1,  0,  0,  1 },
    // Prev = 2
    {  1,  0,  0, -1 },
    // Prev = 3
    { -2, -1,  1,  0 },
  };
#endif
	uint8_t pins = ROTARY_ENCODER_POSITION();

  // No change - do nothing
  if (pins == lastPins) {
    return;
  }

  // Handle case where radio started with encoder not on detent position
  if (skipUntilDetent) {
    if (ON_DETENT(pins)) {
      lastPins = pins;
      skipUntilDetent = 0;
    }
    return;
  }

  // Get increment value for pin state transition
  int inc = reInc[lastPins][pins];
	
//	  if (g_eeGeneral.rotEncMode == ROTARY_ENCODER_MODE_INVERT_BOTH)
//    inc = -inc;
		
		  // Update position change between detents
  reChgPos += inc;

  // Update reported value on full detent change
  if (reChgPos >= ROTARY_ENCODER_GRANULARITY) 
	{
    // If ENTER pressed - ignore scrolling
    if (readKeys(KEY_ENTER) == 0) 
		{
      rotencValue += 1;
    }
    reChgPos -= ROTARY_ENCODER_GRANULARITY;
  } 
	else if (reChgPos <= -ROTARY_ENCODER_GRANULARITY) 
	{
    // If ENTER pressed - ignore scrolling
    if (readKeys(KEY_ENTER) == 0) 
		{
      rotencValue -= 1;
    }
    reChgPos += ROTARY_ENCODER_GRANULARITY;
  }

  lastPins = pins;
	
}
void rotaryEncoderInit(void)
{
	LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOJ);
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOI);
	  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTI, LL_SYSCFG_EXTI_LINE7);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTJ, LL_SYSCFG_EXTI_LINE8);
	  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_7;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.Line_64_95 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_8;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.Line_64_95 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);
	
	  /**/
  LL_GPIO_SetPinPull(GPIOI, LL_GPIO_PIN_7, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinPull(GPIOJ, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);
	  /**/
  LL_GPIO_SetPinMode(GPIOI, LL_GPIO_PIN_7, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(GPIOJ, LL_GPIO_PIN_8, LL_GPIO_MODE_INPUT);
	NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5, 0));
  NVIC_EnableIRQ(EXTI9_5_IRQn);
	MX_TIM17_Init();
	
	  // Get initial position
  lastPins = ROTARY_ENCODER_POSITION();
  skipUntilDetent = !ON_DETENT(lastPins);
	
}

void EXTI9_5_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_7) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);

  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_8) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);

  }

}

/**
  * @brief This function handles TIM17 global interrupt.
  */
void TIM17_IRQHandler(void)
{
  ROTARY_ENCODER_TIMER->SR &= ~TIM_SR_UIF;
  ROTARY_ENCODER_TIMER->CR1 = 0;
  rotaryEncoderCheck();
}


