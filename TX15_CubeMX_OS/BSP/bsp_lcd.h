#ifndef __BSP_LCD_H__
#define __BSP_LCD_H__

#include "bsp_lcd_gpio.h"
#include "font.h"

/*0-0度，1-90度，2-180度，3-270度*/
#define     DIS_DIR		0

//#define TFT_COLUMN_NUMBER 320
//#define TFT_LINE_NUMBER 480
//#define TFT_COLUMN_NUMBER 480
//#define TFT_LINE_NUMBER 320

#define TFT_COLUMN_OFFSET 0


/* R-G-B,565颜色定义 */
#define WHITE                       0xFFFF  /* 白色 √ */
#define BLACK                       0x0000  /* 黑色 */
#define RED                         0xF800  /* 红色 */
#define GREEN                       0x07E0  /* 绿色 √ */
#define BLUE                        0x001F  /* 蓝色 √ */
#define MAGENTA                     0xF81F  /* 品红色 */
#define YELLOW                      0xFFE0  /* 黄色 √ */
#define CYAN                        0x07FF  /* 青色 */
#define BROWN                       0xBC40  /* 棕色 */
#define BRRED                       0xFC07  /* 棕红色 */
#define GRAY                        0x8430  /* 灰色 */
#define DARKBLUE                    0x01CF  /* 深蓝色 */
#define LIGHTBLUE                   0x7D7C  /* 浅蓝色 */
#define GRAYBLUE                    0x5458  /* 灰蓝色 */
#define LIGHTGREEN                  0x841F  /* 浅绿色 */
#define LGRAY                       0xC618  /* 浅灰色 */
#define LGRAYBLUE                   0xA651  /* 浅灰蓝色 */
#define LBBLUE                      0x2B12  /* 浅棕蓝色 */



/* ATK-MD0350模块LCD显示数字模式枚举 */
typedef enum
{
    TFT_NUM_SHOW_NOZERO = 0x00,  /* 数字高位0不显示 */
    TFT_NUM_SHOW_ZERO,           /* 数字高位0显示 */
} tft_num_mode_t;

/* ATK-MD0350模块LCD显示字体枚举 */
typedef enum
{

    TFT_FONT_12 = 0,         /* 12号字体 */
    TFT_FONT_16,             /* 16号字体 */
    TFT_FONT_24,             /* 24号字体 */
    TFT_FONT_32,             /* 32号字体 */

} tft_lcd_font_t;


#define TFT_FONT_12_CHAR_WIDTH   6
#define TFT_FONT_12_CHAR_HEIGHT  12
#define TFT_FONT_12_CHAR_SIZE    12
#define TFT_FONT_16_CHAR_WIDTH   8
#define TFT_FONT_16_CHAR_HEIGHT  16
#define TFT_FONT_16_CHAR_SIZE    16
#define TFT_FONT_24_CHAR_WIDTH   12
#define TFT_FONT_24_CHAR_HEIGHT  24
#define TFT_FONT_24_CHAR_SIZE    36
#define TFT_FONT_32_CHAR_WIDTH   16
#define TFT_FONT_32_CHAR_HEIGHT  32
#define TFT_FONT_32_CHAR_SIZE    64

extern const unsigned char  *point;

void TFT_Clear(uint16_t back_c);									//清除液晶数据，刷黑

void TFT_send_cmd(uint8_t o_command);
void TFT_init(void);        ////ST7796初始化
void TFT_show_char(uint16_t x, uint16_t y, char ch, tft_lcd_font_t font, uint32_t color);
void TFT_show_string(uint16_t x, uint16_t y, uint16_t width, char *str, tft_lcd_font_t font, uint32_t color);  
void TFT_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, tft_num_mode_t mode, tft_lcd_font_t font, uint32_t color);
void TFT_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, tft_lcd_font_t font, uint32_t color);
void TFT_show_Chinese_16x16(uint16_t x,uint16_t y,uint16_t color_char,uint16_t color_back,uint8_t word_number);
void TFT_show_pic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *pic);
void Picture_Display(const uint8_t *ptr_pic);
void TFT_show_negative_num(uint16_t x, uint16_t y, int32_t num, uint8_t len, uint32_t color);
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint32_t color);
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void lcd_show_mp3_name(uint16_t x, uint16_t y, uint16_t width, char *str, uint32_t color);
void TFT_show_flaot_num(uint16_t x, uint16_t y, float num, uint8_t len,uint32_t color);
#endif
