#include <string.h>
#include <stdio.h>
#include "ltdc.h"
#include "bsp_lcd.h"
#include "quadspi.h"
#include "tim.h"

#if LCD_DIR ==0
#define TFT_COLUMN_NUMBER  	320
#define TFT_LINE_NUMBER  	480
#else
#define TFT_COLUMN_NUMBER  	480
#define TFT_LINE_NUMBER  	320
#endif 
/* LCD重要参数 */
uint16_t backlight_pwm = 70;//70%
const unsigned char  *point;

#define LCD_SPI &qspi_tft
 

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

void TFT_init(void)        ////ST7796
{
	TFT_GPIO_init();
	#if BackLight_USE_PWM == 1
    MX_TIM1_Init();
	BackLight_pwm(backlight_pwm);
	#else
	TFT_BL(1);
	#endif
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
/*	SPI_WriteData(0xe0);*/  //28  转90度 		   48 竖	 fc 横 fpc 		  e4
/*	SPI_WriteData(0x08);*/  //28  转90度 		   48 竖	 fc 横 fpc 		  e4
#if LCD_DIR == 0
	SPI_WriteData(0x48);  //0度-0x48,180度-0x88,
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
	SPI_WriteData(0xE8);  //90度-0x28,270度-0xE8


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


void TFT_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
	ltdc_draw_point(x, y, color);
}

/**
 * @brief       平方函数，x^y
 * @param       x: 底数
 *              y: 指数
 * @retval      x^y
 */
static uint32_t TFT_pow(uint8_t x, uint8_t y)
{
    uint8_t loop;
    uint32_t res = 1;
    
    for (loop=0; loop<y; loop++)
    {
        res *= x;
    }
    
    return res;
}

/**
 * @brief       ATK-MD0350模块LCD显示数字，可控制显示高位0
 * @param       x    : 待显示数字的X坐标
 *              y    : 待显示数字的Y坐标
 *              num  : 待显示数字
 *              len  : 待显示数字的位数
 *              mode : TFT_NUM_SHOW_NOZERO: 数字高位0不显示
 *                     TFT_NUM_SHOW_ZERO  : 数字高位0显示
 *              font : 待显示数字的字体
 *              color: 待显示数字的颜色
 * @retval      无
 */
void TFT_show_char(uint16_t x, uint16_t y, char ch, tft_lcd_font_t font, uint32_t color)
{
    const uint8_t *ch_code;
    uint8_t ch_width;
    uint8_t ch_height;
    uint8_t ch_size;
    uint8_t ch_offset;
    uint8_t byte_index;
    uint8_t byte_code;
    uint8_t bit_index;
    uint8_t width_index = 0;
    uint8_t height_index = 0;
    
    ch_offset = ch - ' ';
    switch (font)
    {
        case TFT_FONT_12:
        {
            ch_code = asc2_1206[ch_offset];
            ch_width = TFT_FONT_12_CHAR_WIDTH;
            ch_height = TFT_FONT_12_CHAR_HEIGHT;
            ch_size = TFT_FONT_12_CHAR_SIZE;
            break;
        }


        case TFT_FONT_16:
        {
            ch_code = asc2_1608[ch_offset];
            ch_width = TFT_FONT_16_CHAR_WIDTH;
            ch_height = TFT_FONT_16_CHAR_HEIGHT;
            ch_size = TFT_FONT_16_CHAR_SIZE;
            break;
        }


        case TFT_FONT_24:
        {
            ch_code = asc2_2412[ch_offset];
            ch_width = TFT_FONT_24_CHAR_WIDTH;
            ch_height = TFT_FONT_24_CHAR_HEIGHT;
            ch_size = TFT_FONT_24_CHAR_SIZE;
            break;
        }


        case TFT_FONT_32:
        {
            ch_code = asc2_3216[ch_offset];
            ch_width = TFT_FONT_32_CHAR_WIDTH;
            ch_height = TFT_FONT_32_CHAR_HEIGHT;
            ch_size = TFT_FONT_32_CHAR_SIZE;
            break;
        }

        default:
        {
            return;
        }
    }
    
    if ((x + ch_width > TFT_COLUMN_NUMBER) || (y + ch_height > TFT_LINE_NUMBER))
    {
        return;
    }
	
//    TFT_Clear_char(x,y,x + ch_width,y + ch_height,WHITE); //清除局部背景颜色
	
    for (byte_index=0; byte_index<ch_size; byte_index++)
    {
        byte_code = ch_code[byte_index];
        for (bit_index=0; bit_index<8; bit_index++)
        {
            if ((byte_code & 0x80) != 0)
            {
                TFT_draw_point(x + width_index, y + height_index, color);
            }
            height_index++;
            if (height_index == ch_height)
            {
                height_index = 0;
                width_index++;
                break;
            }
            byte_code <<= 1;
        }
    }
}

/**
 * @brief       ATK-MD0350模块LCD显示字符串
 * @note        会自动换行和换页
 * @param       x     : 待显示字符串的X坐标
 *              y     : 待显示字符串的Y坐标
 *              width : 待显示字符串的显示高度
 *              height: 待显示字符串的显示宽度
 *              str   : 待显示字符串
 *              font  : 待显示字符串的字体
 *              color : 待显示字符串的颜色
 * @retval      无
 */
void TFT_show_string(uint16_t x, uint16_t y, uint16_t width, char *str, tft_lcd_font_t font, uint32_t color)
{
    uint8_t ch_width;
    uint8_t ch_height;
    uint16_t x_raw;
    uint16_t y_raw;
    uint16_t x_limit;
    uint16_t y_limit;
    
    switch (font)
    {
        case TFT_FONT_12:
        {
            ch_width = TFT_FONT_12_CHAR_WIDTH;
            ch_height = TFT_FONT_12_CHAR_HEIGHT;
            break;
        }
        case TFT_FONT_16:
        {
            ch_width = TFT_FONT_16_CHAR_WIDTH;
            ch_height = TFT_FONT_16_CHAR_HEIGHT;
            break;
        }
        case TFT_FONT_24:
        {
            ch_width = TFT_FONT_24_CHAR_WIDTH;
            ch_height = TFT_FONT_24_CHAR_HEIGHT;
            break;
        }
        case TFT_FONT_32:
        {
            ch_width = TFT_FONT_32_CHAR_WIDTH;
            ch_height = TFT_FONT_32_CHAR_HEIGHT;
            break;
        }
        default:
        {
            return;
        }
    }
    
    x_raw = x;
    y_raw = y;
    x_limit = ((x + width + 1) > TFT_COLUMN_NUMBER) ? TFT_COLUMN_NUMBER : (x + width + 1);
    y_limit = ((y + ch_height + 1) > TFT_LINE_NUMBER) ? TFT_LINE_NUMBER : (y + ch_height + 1);
    
    while ((*str >= ' ') && (*str <= '~'))
    {
        if (x + ch_width >= x_limit)
        {
            x = x_raw;
            y += ch_height;
        }
        
        if (y + ch_height >= y_limit)
        {
            y = x_raw;
            x = y_raw;
        }
        
        TFT_show_char(x, y, *str, font, color);
        
        x += ch_width;
        str++;
    }
}

void lcd_show_mp3_name(uint16_t x, uint16_t y, uint16_t width, char *str, uint32_t color)
{
//    ltdc_fill(x,y,x + 8*width*3,y + 16,WHITE);
//    TFT_show_string( x,  y,  width, str, TFT_FONT_16,  color);
	
	uint8_t ch_width;
    uint8_t ch_height;
    uint16_t x_raw;
    uint16_t y_raw;
    uint16_t x_limit;
    uint16_t y_limit;
    
    ch_width = TFT_FONT_16_CHAR_WIDTH;
    ch_height = TFT_FONT_16_CHAR_HEIGHT;

    
    x_raw = x;
    y_raw = y;
    x_limit = ((x + width + 1) > TFT_COLUMN_NUMBER) ? TFT_COLUMN_NUMBER : (x + width + 1);
    y_limit = ((y + ch_height + 1) > TFT_LINE_NUMBER) ? TFT_LINE_NUMBER : (y + ch_height + 1);
    
	ltdc_fill(x,y,x + ch_width * 10,y + ch_width * 2,WHITE);
	
    while ((*str >= ' ') && (*str <= '~'))
    {
        if (x + ch_width >= x_limit)
        {
            x = x_raw;
            y += ch_height;
        }
        
        if (y + ch_height >= y_limit)
        {
            y = x_raw;
            x = y_raw;
        }
        
        TFT_show_char(x, y, *str, TFT_FONT_16, color);
        
        x += ch_width;
        str++;
    }
	
}

void TFT_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, tft_num_mode_t mode, tft_lcd_font_t font, uint32_t color)
{

    uint8_t ch_width;
    uint8_t len_index;
    uint8_t num_index;
    uint8_t first_nozero = 0;
    char pad;
    
    switch (font)
    {

        case TFT_FONT_12:
        {
            ch_width = TFT_FONT_12_CHAR_WIDTH;
            break;
        }


        case TFT_FONT_16:
        {
            ch_width = TFT_FONT_16_CHAR_WIDTH;
            break;
        }

        case TFT_FONT_24:
        {
            ch_width = TFT_FONT_24_CHAR_WIDTH;
            break;
        }

        case TFT_FONT_32:
        {
            ch_width = TFT_FONT_32_CHAR_WIDTH;
            break;
        }

        default:
        {
            return;
        }
    }
    
    switch (mode)
    {
        case TFT_NUM_SHOW_NOZERO:
        {
            pad = ' ';
            break;
        }
        case TFT_NUM_SHOW_ZERO:
        {
            pad = '0';
            break;
        }
        default:
        {
            return;
        }
    }

#if 0
	if(len == 5)
	{
		ltdc_fill(x,y,x + ch_width * 5,y + ch_width * 2,WHITE);
	}
	else
	{
		ltdc_fill(x,y,x + ch_width * 4,y + ch_width * 2,WHITE);
	}
#else
	ltdc_fill(x,y,x + ch_width * len,y + ch_width * 2,WHITE);
#endif

	
    for (len_index=0; len_index<len; len_index++)
    {
        num_index = (num / TFT_pow(10, len - len_index - 1)) % 10;
        if ((first_nozero == 0) && (len_index < (len - 1)))
        {
            if (num_index == 0)
            {
                TFT_show_char(x + ch_width * len_index, y, pad, font, color);
                continue;
            }
            else
            {
                first_nozero = 1;
            }
        }
        
        TFT_show_char(x + ch_width * len_index, y, num_index + '0', font, color);
    }

}



void TFT_show_negative_num(uint16_t x, uint16_t y, int32_t num, uint8_t len, uint32_t color)
{

    uint8_t ch_width;
    uint8_t len_index;
    uint8_t num_index;
    uint8_t first_nozero = 0;
    char pad= ' ';
    
	ch_width = TFT_FONT_16_CHAR_WIDTH;

//	TFT_Clear_char(x-8,y,x + ch_width * 4,y + ch_width * 2,WHITE);
	ltdc_fill(x-8,y,x + ch_width * 4,y + ch_width * 2,WHITE);
	if( num < 0)
	{
		num = -num;
		TFT_show_char(x-8, y, '-', TFT_FONT_16, color);
	}
//	TFT_Clear_char(x,y,x + ch_width * 4,y + ch_width * 2,WHITE);
	
    for (len_index=0; len_index<len; len_index++)
    {
        num_index = (num / TFT_pow(10, len - len_index - 1)) % 10;
        if ((first_nozero == 0) && (len_index < (len - 1)))
        {
            if (num_index == 0)
            {
                TFT_show_char(x + ch_width * len_index, y, pad, TFT_FONT_16, color);
                continue;
            }
            else
            {
                first_nozero = 1;
            }
        }
        
        TFT_show_char(x + ch_width * len_index, y, num_index + '0', TFT_FONT_16, color);
    }

}

/**
 * @brief       ATK-MD0350模块LCD显示数字，不显示高位0
 * @param       x    : 待显示数字的X坐标
 *              y    : 待显示数字的Y坐标
 *              num  : 待显示数字
 *              len  : 待显示数字的位数
 *              font : 待显示数字的字体
 *              color: 待显示数字的颜色
 * @retval      无
 */
void TFT_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, tft_lcd_font_t font, uint32_t color)
{
//	char dispBuff[100];
//	memset(dispBuff,0,sizeof(dispBuff));
//	sprintf(dispBuff," %d ",num);
//	TFT_show_string( x,  y,  len, dispBuff,  font,  color);
   TFT_show_xnum(x, y, num, len, TFT_NUM_SHOW_NOZERO, font, color);
}

//2位小数
void TFT_show_flaot_num(uint16_t x, uint16_t y, float num, uint8_t len,uint32_t color)
{

	uint32_t temp= 0;
	TFT_show_xnum(x, y, (uint32_t)num, len-2, TFT_NUM_SHOW_NOZERO, TFT_FONT_16, color); //显示个小数点前的
	TFT_show_char(x+16, y,'.',TFT_FONT_16,color);
	temp = (uint32_t)(num * 100)%100;
	TFT_show_xnum(x+32, y, temp, 2, TFT_NUM_SHOW_NOZERO, TFT_FONT_16, color); //显示个小数点后的
	
	TFT_show_char(x+56, y,'V',TFT_FONT_16,color);
}

/**
 * @brief       ATK-MD0350模块LCD图片
 * @note        图片取模方式: 水平扫描、RGB565、高位在前
 * @param       x     : 待显示图片的X坐标
 *              y     : 待显示图片的Y坐标
 *              width : 待显示图片的宽度
 *              height: 待显示图片的高度
 *              pic   : 待显示图片数组首地址
 * @retval      无
 */

void TFT_show_pic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *pic)
{

}

void Picture_Display(const uint8_t *ptr_pic)
{

}

/**
 * @brief   画线
 * @param   x1   : 线的起始X坐标
 * @param   y1   : 线的起始Y坐标
 * @param   x2   : 线的结束X坐标
 * @param   y2   : 线的结束Y坐标
 * @param   color: 线的颜色
 * @retval  无
 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    uint16_t t;
    int xerr = 0;
    int yerr = 0;
    int delta_x;
    int delta_y;
    int distance;
    int incx;
    int incy;
    int row;
    int col;
    
    /* 计算坐标增量 */
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    
    row = x1;
    col = y1;
    
    /* 设置X单步方向 */
    if (delta_x > 0)
    {
        incx = 1;
    }
    else if (delta_x == 0)
    {
        incx = 0;
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    
    /* 设置Y单步方向 */
    if (delta_y > 0)
    {
        incy = 1;
    }
    else if (delta_y == 0)
    {
        incy = 0;
    }
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    
    /* 选取基本增量坐标轴 */
    if (delta_x > delta_y)
    {
        distance = delta_x;
    }
    else
    {
        distance = delta_y;
    }
    
    for (t=0; t<=(distance+1); t++)
    {
        ltdc_draw_point(row, col, color);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            row += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            col += incy;
        }
    }
}

/**
 * @brief   画水平线
 * @param   x    : 线的起始X坐标
 * @param   y    : 线的起始Y坐标
 * @param   len  : 线的长度
 * @param   color: 线的颜色
 * @retval  无
 */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color)
{
    if ((len == 0) || (x > TFT_COLUMN_NUMBER) || (y > TFT_LINE_NUMBER))
    {
        return;
    }
    
    ltdc_fill(x, y, x + len - 1, y, color);
}

/**
 * @brief   画矩形
 * @param   x1   : 矩形左上角X坐标
 * @param   y1   : 矩形左上角Y坐标
 * @param   x2   : 矩形右下角X坐标
 * @param   y2   : 矩形右下角Y坐标
 * @param   color: 矩形的颜色
 * @retval  无
 */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    lcd_draw_line(x1, y1, x2, y1, color);
    lcd_draw_line(x1, y1, x1, y2, color);
    lcd_draw_line(x1, y2, x2, y2, color);
    lcd_draw_line(x2, y1, x2, y2, color);
}

/**
 * @brief   画圆
 * @param   x0   : 圆心的X坐标
 * @param   y0   : 圆心的Y坐标
 * @param   r    : 圆的半径
 * @param   color: 圆的颜色
 * @retval  无
 */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint32_t color)
{
    int a;
    int b;
    int di;
    
    a = 0;
    b = r;
    di = 3 - (r << 1);  /* 判断下个点位置的标志 */
    
    while (a <= b)      /* 使用Bresenham算法画圆 */
    {
        ltdc_draw_point(x0 + a, y0 - b, color);
        ltdc_draw_point(x0 + b, y0 - a, color);
        ltdc_draw_point(x0 + b, y0 + a, color);
        ltdc_draw_point(x0 + a, y0 + b, color);
        ltdc_draw_point(x0 - a, y0 + b, color);
        ltdc_draw_point(x0 - b, y0 + a, color);
        ltdc_draw_point(x0 - a, y0 - b, color);
        ltdc_draw_point(x0 - b, y0 - a, color);
        a++;
        if (di < 0)
        {
            di += 4 * a + 6;
        }
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}



