#ifndef __TAS2505_H__
#define __TAS2505_H__
#include "main.h"
#include "i2c.h"
#include "i2s.h"


#define TAS2505_I2C  				&hi2c4
#define TAS2505_I2C_ADDRESS  		0x30

#define TAS2505_I2C_TIMEOUT         1000

#define TAS2505_RST_GPIO_PORT            GPIOH
#define TAS2505_RST_GPIO_PIN             GPIO_PIN_10
#define TAS2505_RST_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOH_CLK_ENABLE(); } while (0)

//耳机接口检测GPIO
#define HEAD_DET_GPIO_PORT            GPIOA
#define HEAD_DET_GPIO_PIN             GPIO_PIN_5
#define HEAD_DET_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)


#define TAS2505_RST_Set(x)              do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TAS2505_RST_GPIO_PORT, TAS2505_RST_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TAS2505_RST_GPIO_PORT, TAS2505_RST_GPIO_PIN, GPIO_PIN_RESET);   \
                                        } while (0)

#define      HEAD_PHONE_DET        HAL_GPIO_ReadPin(HEAD_DET_GPIO_PORT, HEAD_DET_GPIO_PIN)

#define      MAX_INDEX		19 

/* 状态 */
enum
{
	STA_IDLE = 0,	/* 待机状态 */
	STA_PLAYING,	/* 放音状态 */
	STA_ERR,			/*  error  */
};
#define DIS_VOLUME		70
#define VOLUME		127 - DIS_VOLUME
/* 状态 */
enum
{
	KEY_IDLE = 0,	
	KEY_PLAY,	
	KEY_STOP,
	KEY_NEXT,
	KEY_LAST,
	KEY_VOL_UP,
	KEY_VOL_DOWN		
};

typedef struct
{
	uint8_t ucVolume;			/* 当前放音音量 */
	uint8_t ucStatus;			/* 状态，0表示待机，1表示播放中，2 出错 */	
	uint32_t ucFreq;			/* 采样频率 */
}MP3_TYPE;	

typedef struct
{
	uint8_t Volume:7;		/* 音量,0-116,0最大，116最小 */
	uint8_t Dis_Volume:7;	
	uint8_t HP_status;	/* 耳机插入状态 */
	uint8_t key_status;	/* 按键状态 */
	uint8_t index;
  uint8_t next_flg;
  uint8_t last_flg;
}tas2505_TYPE;	

extern tas2505_TYPE audio;
extern uint8_t sd_sta;
extern MP3_TYPE mp3player;
extern char *MP3_file[];
extern uint8_t Index;
enum 
{
	USE_HP = 1,
	USE_SPK= 0
};
	
void TAS2505_Init(void);
void audio_TAS2505_loop(void);
void setting_volume_HP(uint8_t volume);
void setting_volume_SPK(uint8_t volume);
void setting_max_volume_SPK(void);
void switch_player_device(uint8_t dev);
void MusicPlayer_I2S_DMA_TX_Callback(void);
#endif 
