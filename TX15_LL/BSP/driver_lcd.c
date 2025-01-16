
#include "driver_lcd.h"
#include "hal.h"
#include "ltdc.h"
#include "driver_delays.h"

static void LCD_Delay(void) 
{
  volatile uint16_t i;

  for (i = 0; i < 20; i++) {
    ;
  }
}

static void lcdSpiConfig(void) 
{
  LL_GPIO_InitTypeDef GPIO_InitStructure;
  LL_GPIO_StructInit(&GPIO_InitStructure);

  GPIO_InitStructure.Pin        = LCD_SPI_SCK_GPIO_PIN | LCD_SPI_MOSI_GPIO_PIN;
  GPIO_InitStructure.Speed      = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStructure.Mode       = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStructure.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LCD_SPI_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.Pin        = LCD_SPI_CS_GPIO_PIN;
  LL_GPIO_Init(LCD_SPI_CS_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.Pin        = LCD_RESET_GPIO_PIN;
  LL_GPIO_Init(LCD_RESET_GPIO, &GPIO_InitStructure);

  LCD_CS_HIGH();
}


void lcdDelay() {
  delay_01us(1);
}

static void lcdReset() {
  LCD_CS_HIGH();

  LCD_NRST_HIGH();
  delay_ms(1);

  LCD_NRST_LOW(); // RESET();
  delay_ms(10);

  LCD_NRST_HIGH();
  delay_ms(100);
}

static uint8_t LCD_ReadByteOnFallingEdge(void) 
{
  uint16_t i;
  uint8_t ReceiveData = 0;

  LCD_MOSI_HIGH();
  LCD_MOSI_AS_INPUT();

  for (i = 0; i < 8; i++) {
    LCD_DELAY();
    LCD_SCK_HIGH();
    LCD_DELAY();
    LCD_DELAY();
    ReceiveData <<= 1;

    LCD_SCK_LOW();
    LCD_DELAY();
    LCD_DELAY();
    if (LCD_READ_DATA_PIN()) {
      ReceiveData |= 0x01;
    }
  }

  LCD_MOSI_AS_OUTPUT();

  return (ReceiveData);
}

static void lcdWriteByte(uint8_t data_enable, uint8_t byte) 
{

  LCD_SCK_LOW();
  lcdDelay();

  if (data_enable) {
    LCD_MOSI_HIGH();
  } else {
    LCD_MOSI_LOW();
  }

  LCD_SCK_HIGH();
  lcdDelay();

  for (int i = 0; i < 8; i++) {
    LCD_SCK_LOW();
    lcdDelay();

    if (byte & 0x80) {
      LCD_MOSI_HIGH();
    } else {
      LCD_MOSI_LOW();
    }

    LCD_SCK_HIGH();
    byte <<= 1;

    lcdDelay();
  }

  LCD_SCK_LOW();
}

static uint8_t LCD_ReadByte(void) 
{
  uint16_t i;
  uint8_t ReceiveData = 0;

  LCD_MOSI_HIGH();                     
  LCD_MOSI_AS_INPUT();
  for (i = 0; i < 8; i++) {
    LCD_SCK_LOW();
    lcdDelay();
    ReceiveData <<= 1;
    LCD_SCK_HIGH();
    lcdDelay();
    if (LCD_READ_DATA_PIN()) {
      ReceiveData |= 0x01;
    }
  }
  LCD_SCK_LOW();
  LCD_MOSI_AS_OUTPUT();
  return (ReceiveData);
}

static uint8_t LCD_ReadRegister(unsigned char Register) 
{
  uint8_t ReadData = 0;
  LCD_CS_LOW();
  lcdDelay();

  lcdWriteByte(0, Register);
  lcdDelay();
  lcdDelay();
  ReadData = LCD_ReadByte();
  LCD_CS_HIGH();
  return (ReadData);
}

void lcdWriteCommand(uint8_t command) 
{
  lcdWriteByte(0, command);
}

static void lcdWriteData(uint8_t data) 
{
  lcdWriteByte(1, data);
}

void LCD_ST7365_On(void) {
  LCD_CS_LOW();
  delay_ms(1);
  lcdWriteCommand(0x29);
  LCD_CS_HIGH();
}

void LCD_ST7365_Init(void) {

  LCD_CS_LOW();
  delay_ms(1);
  lcdWriteCommand( 0x11 );
  delay_ms(120);

  lcdWriteCommand( 0xF0 );
  lcdWriteData( 0xC3 );

  lcdWriteCommand( 0xF0 );
  lcdWriteData( 0x96 );


  lcdWriteCommand(0x11);

  delay_ms(120);

  lcdWriteCommand(0xF0);     // Command Set Control
  lcdWriteData(0xC3);

  lcdWriteCommand(0xF0);
  lcdWriteData(0x96);

  lcdWriteCommand(0x36);     // Memory Data Access Control MY,MX~~
  lcdWriteData(0xE8);

  lcdWriteCommand(0x2A);//480-1
  lcdWriteData(0x00);
  lcdWriteData(0x00);
  lcdWriteData(0x01);
  lcdWriteData(0xDF);

  lcdWriteCommand(0x2B);
  lcdWriteData(0x00);
  lcdWriteData(0x00);
  lcdWriteData(0x01);
  lcdWriteData(0x3F); //320-1


  lcdWriteCommand(0x3A);
  lcdWriteData(0x66);   //55:RGB565 66:RGB666 77:RGB888

  lcdWriteCommand(0xB4);
  lcdWriteData(0x01);

  lcdWriteCommand(0xB6);    //RGB
  lcdWriteData(0x20);
  lcdWriteData(0x02);     //02
  lcdWriteData(0x3B);

  lcdWriteCommand(0xB7);
  lcdWriteData(0xC6);

  lcdWriteCommand(0xC0);
  lcdWriteData(0x80);
  lcdWriteData(0x45);

  lcdWriteCommand(0xC1);
  lcdWriteData(0x0F );   //18  //00

  lcdWriteCommand(0xC2);
  lcdWriteData(0xA7);   //A7

  lcdWriteCommand(0xC5);
  lcdWriteData(0x0A);

  lcdWriteCommand(0xE8);
  lcdWriteData(0x40);
  lcdWriteData(0x8A);
  lcdWriteData(0x00);
  lcdWriteData(0x00);
  lcdWriteData(0x29);
  lcdWriteData(0x19);
  lcdWriteData(0xA5);
  lcdWriteData(0x33);

  lcdWriteCommand(0xE0);
  lcdWriteData(0xD0);
  lcdWriteData(0x08);
  lcdWriteData(0x0F);
  lcdWriteData(0x06);
  lcdWriteData(0x06);
  lcdWriteData(0x33);
  lcdWriteData(0x30);
  lcdWriteData(0x33);
  lcdWriteData(0x47);
  lcdWriteData(0x17);
  lcdWriteData(0x13);
  lcdWriteData(0x13);
  lcdWriteData(0x2B);
  lcdWriteData(0x31);

  lcdWriteCommand(0xE1);
  lcdWriteData(0xD0);
  lcdWriteData(0x0A);
  lcdWriteData(0x11);
  lcdWriteData(0x0B);
  lcdWriteData(0x09);
  lcdWriteData(0x07);
  lcdWriteData(0x2F);
  lcdWriteData(0x33);
  lcdWriteData(0x47);
  lcdWriteData(0x38);
  lcdWriteData(0x15);
  lcdWriteData(0x16);
  lcdWriteData(0x2C);
  lcdWriteData(0x32);


  lcdWriteCommand(0xF0);
  lcdWriteData(0x3C);

  lcdWriteCommand(0xF0);
  lcdWriteData(0x69);

  delay_ms(120);

  lcdWriteCommand(0x21);
  LCD_CS_HIGH();
  delay_ms(1);
  LCD_ST7365_On();
}

void LCD_ST7365_Off(void) {
  LCD_CS_LOW();
  delay_ms(1);
  lcdWriteCommand(0x28);
  LCD_CS_HIGH();
}

void lcdSetInitalFrameBuffer(void* fbAddress)
{
  initialFrameBuffer = fbAddress;
};

void lcdInit(void)
{
	lcdSpiConfig();
	lcdReset();
	LCD_ST7365_Init();
	MX_LTDC_Init();

}
