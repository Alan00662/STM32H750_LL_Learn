#include "driver_lcd.h"


#if LCD_DIR ==0
#define TFT_COLUMN_NUMBER  	320
#define TFT_LINE_NUMBER  	480
#else
#define TFT_COLUMN_NUMBER  	480
#define TFT_LINE_NUMBER  	320
#endif 

uint16_t backlight_pwm = 70;//70%
const unsigned char  *point;

static void TFT_GPIO_init(void)
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
  

  GPIO_InitStruct.Pin = TFT_BL_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(TFT_BL_GPIO_PORT, &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_SET);
  

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
  
}


static void SPI_SendData(unsigned char i)
{  
	unsigned char n;
	
	for(n=0; n<8; n++)			
	{  
	if(i&0x80) 
	{
		TFT_MOSI(1);
	}
	else 
	{
		TFT_MOSI(0);
	}
	i<<= 1;
	
	TFT_CLK(0);//_nop_(); _nop_();_nop_();_nop_();
	TFT_CLK(1);;//_nop_();_nop_();_nop_();_nop_();
	}
}

static void SPI_WriteComm(unsigned char i)
{
    TFT_CS(0);

    TFT_MOSI(0);

	TFT_CLK(0);
	TFT_CLK(1);

	SPI_SendData(i);

    TFT_CS(1);
}

static void SPI_WriteData(unsigned char i)
{
    TFT_CS(0);

    TFT_MOSI(1);

	TFT_CLK(0);
	TFT_CLK(1);

	SPI_SendData(i);

    TFT_CS(1);
}

void st7796_init(void)        ////ST7796
{
	TFT_GPIO_init();

	TFT_BL(1);
	
	TFT_CS(0);
	TFT_RST(1);	
	HAL_Delay(100);	 
	TFT_RST(0);
	HAL_Delay(200);	 
	TFT_RST(1);	
	HAL_Delay(200);	 
	//************ Reset LCD Driver****************//       

	SPI_WriteComm(0x11);     
	
	HAL_Delay(120);           
	
	SPI_WriteComm(0xF0);     // Command Set Control
	SPI_WriteData(0xC3);   
	
	SPI_WriteComm(0xF0);     
	SPI_WriteData(0x96); 
	
	SPI_WriteComm(0x36);     // Memory Data Access Control MY,MX~~
/*	SPI_WriteData(0xe0);*/  //28  ת90�� 		   48 ��	 fc �� fpc 		  e4
/*	SPI_WriteData(0x08);*/  //28  ת90�� 		   48 ��	 fc �� fpc 		  e4
#if LCD_DIR == 0
//	SPI_WriteData(0x48);  //180��-0x48,0��-0x88,
	SPI_WriteData(0x88);  
	SPI_WriteComm(0x2A);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x01);
	SPI_WriteData(0x3F); //320-1
	
	SPI_WriteComm(0x2B);//480-1
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x01);
	SPI_WriteData(0xDF);
	
#else
	SPI_WriteData(0xE8);  //90��-0x28,270��-0xE8


	SPI_WriteComm(0x2A);//480-1
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x01);
	SPI_WriteData(0xDF);
	
	SPI_WriteComm(0x2B);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x01);
	SPI_WriteData(0x3F); //320-1
#endif	

	SPI_WriteComm(0x3A);     
	SPI_WriteData(0x66);   //55:RGB565 66:RGB666 77:RGB888 
	/*
	SPI_WriteComm(0xB0);
	SPI_WriteData(0x80); 
	*/
	SPI_WriteComm(0xB4);     
	SPI_WriteData(0x01);

	
	SPI_WriteComm(0xB6);    //RGB 
	SPI_WriteData(0x20);
	SPI_WriteData(0x02);	 //02
	SPI_WriteData(0x3B);  
	
	SPI_WriteComm(0xB7);     
	SPI_WriteData(0xC6);   
	
	SPI_WriteComm(0xC0);     
	SPI_WriteData(0x80);   
	SPI_WriteData(0x45);   
	
	SPI_WriteComm(0xC1);     
	SPI_WriteData(0x0F );   //18  //00

	SPI_WriteComm(0xC2);     
	SPI_WriteData(0xA7);   //A7
	
	SPI_WriteComm(0xC5);     
	SPI_WriteData(0x0A);   
	
	SPI_WriteComm(0xE8);     
	SPI_WriteData(0x40);
	SPI_WriteData(0x8A);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x29);
	SPI_WriteData(0x19);
	SPI_WriteData(0xA5);
	SPI_WriteData(0x33);
	
	SPI_WriteComm(0xE0);
	SPI_WriteData(0xD0);
	SPI_WriteData(0x08);
	SPI_WriteData(0x0F);
	SPI_WriteData(0x06);
	SPI_WriteData(0x06);
	SPI_WriteData(0x33);
	SPI_WriteData(0x30);
	SPI_WriteData(0x33);
	SPI_WriteData(0x47);
	SPI_WriteData(0x17);
	SPI_WriteData(0x13);
	SPI_WriteData(0x13);
	SPI_WriteData(0x2B);
	SPI_WriteData(0x31);
	
	SPI_WriteComm(0xE1);
	SPI_WriteData(0xD0);
	SPI_WriteData(0x0A);
	SPI_WriteData(0x11);
	SPI_WriteData(0x0B);
	SPI_WriteData(0x09);
	SPI_WriteData(0x07);
	SPI_WriteData(0x2F);
	SPI_WriteData(0x33);
	SPI_WriteData(0x47);
	SPI_WriteData(0x38);
	SPI_WriteData(0x15);
	SPI_WriteData(0x16);
	SPI_WriteData(0x2C);
	SPI_WriteData(0x32);
	
	
	SPI_WriteComm(0xF0);     
	SPI_WriteData(0x3C);   
	
	SPI_WriteComm(0xF0);     
	SPI_WriteData(0x69);  
	
	HAL_Delay(120);                
	
	SPI_WriteComm(0x21);     
	
	SPI_WriteComm(0x29); 
	
}

