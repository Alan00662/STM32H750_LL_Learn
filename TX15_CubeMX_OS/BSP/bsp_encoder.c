
#include "bsp_encoder.h"
#include "tim.h"
#include "usart.h"

#define Dir 0

int32_t Encoder = 0;


void Encoder_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};


    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    /**TIM8 GPIO Configuration
    PI7     ------> TIM8_CH2
    PJ8     ------> TIM8_CH1
    */
    GPIO_InitStruct.Pin = ROTENC_A_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; 
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ROTENC_A_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ROTENC_B_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ROTENC_B_GPIO_PORT, &GPIO_InitStruct);
	
		HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);


}


void EXTI9_5_IRQHandler(void)
{

static uint8_t edgeA = 0;
static uint8_t edgeB = 0;


  if (__HAL_GPIO_EXTI_GET_IT(ROTENC_A_GPIO_PIN) != 0x00U) 
  {
	 __HAL_GPIO_EXTI_CLEAR_IT(ROTENC_A_GPIO_PIN);
		if(edgeA == 0) //ÏÂ½µÑØ
		{
			if (ROTENC_B == 1)
			{
				Encoder++;						
			}
			else
			{
				Encoder--;
			}
			edgeA = 1;
		}
		else if(edgeA == 1) //ÉÏÉýÑØ
		{
			if (ROTENC_B == 0)
			{		
				Encoder++;				

			}
			else
			{

				Encoder--;
			}
				edgeA = 0;
		}

  }

  
  else if (__HAL_GPIO_EXTI_GET_IT(ROTENC_B_GPIO_PIN) != 0x00U) 
  {

	__HAL_GPIO_EXTI_CLEAR_IT(ROTENC_B_GPIO_PIN);
		#if Dir
		if(edgeB == 0) //ÏÂ½µÑØ
		{
			edgeB = 1;
			if (ROTENC_A ==0)
			{
			
					Encoder++;
			}
			else
				Encoder--;
		}
		else if(edgeB == 1) //ÉÏÉýÑØ
		{
			edgeB = 0;
			if (ROTENC_A == 1)
			{
			
					Encoder++;
			}
			else
				Encoder--;
		}
  #endif
  }

}