#include "string.h"
#include "bsp_tas2505.h"
#include "mp3dec.h"
#include "ff.h"
#include "main.h"
#include "bsp_sdio_sd.h"
char *MP3_file[] = {
	"0:/000.mp3",
	"0:/001.mp3",
	"0:/002.mp3",
	"0:/003.mp3",
	"0:/004.mp3",
	"0:/005.mp3",
  "0:/006.mp3",
  "0:/007.mp3",
  "0:/008.mp3",
  "0:/009.mp3",
	"0:/010.mp3",
	"0:/011.mp3",
	"0:/012.mp3",
	"0:/013.mp3",
	"0:/014.mp3",
	"0:/015.mp3",
  "0:/016.mp3",
  "0:/017.mp3",
  "0:/018.mp3",
  "0:/019.mp3",	
};
static void audio_TAS2505_in_play_loop(void);
extern void touch_Loop(void);
/* 推荐使用以下格式mp3文件：
 * 采样率：44100Hz
 * 声  道：2
 * 比特率：320kbps
 */

/* 处理立体声音频数据时，输出缓冲区需要的最大大小为2304*16/8字节(16为PCM数据为16位)，
 * 这里我们定义MP3BUFFER_SIZE为2304，实际输出缓冲区为MP3BUFFER_SIZE*2个字节
 */
#define MP3BUFFER_SIZE  2304		
#define INPUTBUF_SIZE   3000

HMP3Decoder			Mp3Decoder={0};					 /* mp3解码器指针	*/
MP3FrameInfo		Mp3FrameInfo={0};				 /* mP3帧信息  */
MP3_TYPE				mp3player = {0};         /* mp3播放设备 */

uint8_t inputbuf[INPUTBUF_SIZE]={0};        /* 解码输入缓冲区，1940字节为最大MP3帧大小  */
__attribute__((at(0x24030000))) short outbuffer[2][MP3BUFFER_SIZE];  /* 解码输出缓冲区，也是I2S输入数据，实际占用字节数：RECBUFFER_SIZE*2 */

FIL file;											/* file objects */
FRESULT result; 
UINT bw;            					/* File R/W count */

volatile uint8_t Isread=0;           /* DMA传输完成标志 */
uint8_t bufflag=0;          /* 数据缓存区选择标志 */

uint32_t pcm_data_size;  //缓冲区的大小(单位: 字节) 
uint32_t pkg_size;       //一包数据的大小
int   cur_use_idx;    //当前所使用的PCM数据缓冲区

uint8_t IsNext = 0;
uint8_t IsLast = 0;

uint8_t Index = 0;
tas2505_TYPE audio=
{
	.Volume = VOLUME,
	.Dis_Volume = DIS_VOLUME,
	.HP_status = USE_SPK,
	.index = 0,
  .last_flg =0,
  .next_flg =0,
};

uint8_t sd_sta = 0; 
static void tas2505_gpio_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TAS2505_RST_GPIO_CLK_ENABLE();
    HEAD_DET_GPIO_CLK_ENABLE();
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(TAS2505_RST_GPIO_PORT, TAS2505_RST_GPIO_PIN, GPIO_PIN_RESET);

    /*Configure GPIO pins : PIPin PIPin PIPin */
    GPIO_InitStruct.Pin = TAS2505_RST_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TAS2505_RST_GPIO_PORT, &GPIO_InitStruct);

    /*Configure GPIO pins : PIPin PIPin PIPin */
    GPIO_InitStruct.Pin = HEAD_DET_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(HEAD_DET_GPIO_PORT, &GPIO_InitStruct);

}

// 写入 TAS2505 寄存器
static void TAS2505_WriteRegister(uint8_t reg, uint8_t data)
{
    uint8_t buffer[1];
    buffer[0] = data;

    HAL_I2C_Mem_Write(TAS2505_I2C, TAS2505_I2C_ADDRESS, reg,1,buffer, 1, TAS2505_I2C_TIMEOUT);
}

// 写入 TAS2505 寄存器
static void TAS2505_ReadRegister(uint8_t page,uint8_t reg, uint8_t* data)
{
	if(page ==1)
	{
		TAS2505_WriteRegister(0x00,0x01);
	}
	else
	{
		TAS2505_WriteRegister(0x00,0x00);
	}
    HAL_I2C_Mem_Read(TAS2505_I2C, TAS2505_I2C_ADDRESS, reg,1,data, 1, TAS2505_I2C_TIMEOUT);
}

HAL_StatusTypeDef sta = 0;

static void SendAudioData(uint16_t *pData, uint16_t Size)
{
    sta = HAL_I2S_Transmit(&hi2s2, pData, Size, HAL_MAX_DELAY);
	
}


void mp3PlayerDemo(const char *mp3file)
{
	uint8_t *read_ptr=inputbuf;
	int err=0, i=0, outputSamps=0;	
	int	read_offset = 0;				/* 读偏移指针 */
	int	bytes_left = 0;					/* 剩余字节数 */	
	
	mp3player.ucFreq=I2S_AUDIOFREQ_DEFAULT;
	mp3player.ucStatus=STA_IDLE;
	mp3player.ucVolume=40;
	
	result=f_open(&file,mp3file,FA_READ);
	if(result!=FR_OK)
	{
		debug_tx5("Open mp3file :%s fail!!!->%d\r\n",mp3file,result);
		result = f_close (&file);
		return;	/* 停止播放 */
	}
	else
	debug_tx5("open file ok, -> %s\n",mp3file);
	
	//初始化MP3解码器
	Mp3Decoder = MP3InitDecoder();	
	if(Mp3Decoder==0)
	{
		debug_tx5("init helix deive\n");
		return;	/* 停止播放 */
	}
	
	bufflag=0;
	Isread=0;
	
	mp3player.ucStatus = STA_PLAYING;		/* 放音状态 */
  result=f_read(&file,inputbuf,INPUTBUF_SIZE,&bw);
	if(result!=FR_OK)
	{
		debug_tx5("read1 %s failed -> %d\r\n",mp3file,result);
		MP3FreeDecoder(Mp3Decoder);
		return;
	}
	read_ptr=inputbuf;
	bytes_left=bw;
	/* 进入主程序循环体 */
	while(mp3player.ucStatus == STA_PLAYING)
	{
		read_offset = MP3FindSyncWord(read_ptr, bytes_left);	//寻找帧同步，返回第一个同步字的位置
		if(read_offset < 0)										//没有找到同步字
		{
			result=f_read(&file,inputbuf,INPUTBUF_SIZE,&bw);
			if(result!=FR_OK)
			{
				debug_tx5("read2 %s failed -> %d\r\n",mp3file,result);
				break;
			}
			read_ptr=inputbuf;
			bytes_left = bw;
			continue;		//跳出循环2，回到循环1	
		}
		read_ptr += read_offset;				//偏移至同步字的位置
		bytes_left -= read_offset;				//同步字之后的数据大小	
		if(bytes_left < 1024)							//补充数据
		{
			/* 注意这个地方因为采用的是DMA读取，所以一定要4字节对齐  */
			i=(uint32_t)(bytes_left)&3;			//判断多余的字节
			if(i) i=4-i;						//需要补充的字节
			memcpy(inputbuf+i, read_ptr, bytes_left);	//从对齐位置开始复制
			read_ptr = inputbuf+i;										//指向数据对齐位置
			result = f_read(&file, inputbuf+bytes_left+i, INPUTBUF_SIZE-bytes_left-i, &bw);//补充数据
			if(result!=FR_OK)
			{
				debug_tx5("read3 %s failed -> %d\r\n",mp3file,result);
				break;
			}
			bytes_left += bw;		//有效数据流大小
		}
		//bufflag开始解码 参数：mp3解码结构体、输入流指针、输入流大小、输出流指针、数据格式
		err = MP3Decode(Mp3Decoder, &read_ptr, &bytes_left, outbuffer[bufflag], 0);	
		if (err != ERR_MP3_NONE)	//错误处理
		{
			switch (err)
			{
				case ERR_MP3_INDATA_UNDERFLOW:
					debug_tx5("ERR_MP3_INDATA_UNDERFLOW\r\n");
					result = f_read(&file, inputbuf, INPUTBUF_SIZE, &bw);
					read_ptr = inputbuf;
					bytes_left = bw;
					break;		
				case ERR_MP3_MAINDATA_UNDERFLOW:
					/* do nothing - next call to decode will provide more mainData */
					debug_tx5("ERR_MP3_MAINDATA_UNDERFLOW\r\n");
					break;		
				default:
					debug_tx5("UNKNOWN ERROR:%d\r\n", err);		
					if (bytes_left > 0)
					{
						bytes_left --;
						read_ptr ++;
					}	
					break;
			}
			Isread=1;
		}
		else //解码无错误，准备把数据输出到PCM
		{
			MP3GetLastFrameInfo(Mp3Decoder, &Mp3FrameInfo);		//获取解码信息				
			/* 输出到DAC */
			outputSamps = Mp3FrameInfo.outputSamps;							//PCM数据个数
			if (outputSamps > 0)
			{
				if (Mp3FrameInfo.nChans == 1)	//单声道
				{
					//单声道数据需要复制一份到另一个声道
					for (i = outputSamps - 1; i >= 0; i--)
					{
						outbuffer[bufflag][i * 2] = outbuffer[bufflag][i];
						outbuffer[bufflag][i * 2 + 1] = outbuffer[bufflag][i];
					}
					outputSamps *= 2;
				}
			}
			
			/* 根据解码信息设置采样率 */
			if (Mp3FrameInfo.samprate != mp3player.ucFreq)	//采样率 
			{
				mp3player.ucFreq = Mp3FrameInfo.samprate;
				
				debug_tx5(" \r\n Bitrate       %dKbps", Mp3FrameInfo.bitrate/1000);
				debug_tx5(" \r\n Samprate      %dHz", mp3player.ucFreq);
				debug_tx5(" \r\n BitsPerSample %db", Mp3FrameInfo.bitsPerSample);
				debug_tx5(" \r\n nChans        %d", Mp3FrameInfo.nChans);
				debug_tx5(" \r\n Layer         %d", Mp3FrameInfo.layer);
				debug_tx5(" \r\n Version       %d", Mp3FrameInfo.version);
				debug_tx5(" \r\n OutputSamps   %d", Mp3FrameInfo.outputSamps);
				debug_tx5("\r\n");
				if(mp3player.ucFreq >= I2S_AUDIOFREQ_DEFAULT)	//I2S_AudioFreq_Default = 2，正常的帧，每次都要改速率
				{
          
					I2Sx_Mode_Config(I2S_STANDARD_PHILIPS,I2S_DATAFORMAT_16B,mp3player.ucFreq);						//根据采样率修改iis速率
					I2Sx_TX_DMA_Init();
					I2S_SEND((uint32_t)(&outbuffer[0]),(uint32_t)&outbuffer[1],outputSamps);				
				}
				
				I2S_Play_Start();
			}
		}
		
		if(file.fptr==file.fsize) 		//mp3文件读取完成，退出
		{
			debug_tx5("END\r\n");
			break;
		}	
		
		ltdc_clear(WHITE);
		while(Isread==0)	//音频数据还在穿传输中
		{
			led_Loop_bink(400);
			key_scan_Loop();
			Read_TCP9539_Loop();
			audio_TAS2505_in_play_loop();
			MP3_Menu_Display();
		}
		Isread=0;
		
	}
	I2S_Stop();
	mp3player.ucStatus=STA_IDLE;
	MP3FreeDecoder(Mp3Decoder);
	f_close(&file);	
	ltdc_clear(WHITE);
}



uint32_t tas2505_in_play_tick = 0;
static void audio_TAS2505_in_play_loop(void)
{
	static uint8_t volum_add_cnt = 0;
	static uint8_t volum_dis_cnt = 0;
	static uint8_t ctrl_cnt = 0;
    static uint8_t next_cnt = 0;
	static uint8_t last_cnt = 0;
	
	if((HAL_GetTick() - tas2505_in_play_tick) > 12)
	{
		sd_sta = SD_PRESENT? 1:0; //是否插上SD卡
		
		audio.HP_status = HEAD_PHONE_DET?1:0;
		switch_player_device(audio.HP_status);
		
		if(Tca9539_sw.SF == 0)
		{
			ctrl_cnt++;			
		}
		else
		{
			if(ctrl_cnt > 4)
			{				
				debug_tx5("mp3player stop\r\n");
				mp3player.ucStatus=STA_IDLE;
				IsNext = 0;	
				IsLast = 0;					
			}
			ctrl_cnt = 0;
			
		}
			
		if(Trim_info.lhl == 0)
		{
			volum_add_cnt ++;
			if(volum_add_cnt>5)//消除抖动
			{
				volum_add_cnt = 0;
				audio.Volume +=1;
				audio.Dis_Volume = 127 - audio.Volume;
				if(audio.Volume>127)
				{
					audio.Volume = 127;
				}
				if(audio.HP_status == USE_HP)
				{
					setting_volume_HP(audio.Volume);
				}
				else
				{
					setting_volume_SPK(audio.Volume);
				}
				
								
			}
		}
		else 
		{
			volum_add_cnt = 0;
			
		}
		if(Trim_info.lhr == 0) //按下
		{
			volum_dis_cnt ++;
			if(volum_dis_cnt > 5)//消除抖动
			{
				volum_dis_cnt = 0;
				audio.Volume-=1;
				audio.Dis_Volume = 127 - audio.Volume;
				if(audio.Volume<1)
					audio.Volume = 0;
				if(audio.HP_status == USE_HP)
				{
					setting_volume_HP(audio.Volume);
				}
				else
				{
					setting_volume_SPK(audio.Volume);
				}
			}			
		}
		else //松开手
		{
			volum_dis_cnt = 0;
		}
        if(Key_info.right == 0) //下一曲
		{
			next_cnt++;

		}
		else
		{
			if(next_cnt > 3)
			{
				mp3player.ucStatus=STA_IDLE;
				IsNext = 1;

            }
            next_cnt = 0;
        }
		
		if(Key_info.left == 0) //上一曲
		{
			last_cnt++;

		}
		else
		{
			if(last_cnt > 3)
			{
				mp3player.ucStatus=STA_IDLE;
				IsLast = 1;

            }
            last_cnt = 0;
        }

		tas2505_in_play_tick = HAL_GetTick();
	}
}

uint32_t tas2505_tick = 0;
void audio_TAS2505_loop(void)
{
	static uint8_t volum_add_cnt = 0;
	static uint8_t volum_dis_cnt = 0;
	static uint8_t ctrl_cnt = 0;
	static uint8_t next_cnt = 0;
	static uint8_t last_cnt = 0;
	if((HAL_GetTick() - tas2505_tick) > 10)
	{
		sd_sta = SD_PRESENT? 1:0; //是否插上SD卡
		
		if(Tca9539_sw.SF == 0) //播放
		{
			ctrl_cnt++;

		}
		else
		{
			if(ctrl_cnt > 3)
			{
				mp3PlayerDemo(MP3_file[audio.index]);
			}
			ctrl_cnt = 0;
		}
		
		if(Key_info.right == 0) //下一曲
		{
			next_cnt++;

		}
		else
		{
			if(next_cnt > 3)
			{
				audio.index +=1;
        if(audio.index >= MAX_INDEX) audio.index = MAX_INDEX;
				
				mp3PlayerDemo(MP3_file[audio.index]);


			}				
				
			next_cnt = 0;
		}
		
		if(Key_info.left == 0) //上一曲
		{
			last_cnt++;
		}
		else
		{
			if(last_cnt > 3)
			{

				audio.index -=1;

				if(audio.index <= 0) audio.index = 0;
				mp3PlayerDemo(MP3_file[audio.index]);

			}				
				
			last_cnt = 0;
		}
		if(IsLast)
		{
			IsLast = 0;
			audio.index -=1;
			if(audio.index <= 0) audio.index = 0;
			mp3PlayerDemo(MP3_file[audio.index]);
		}
		if(IsNext)
		{
			IsNext = 0;
			audio.index +=1;
            if(audio.index >= MAX_INDEX) audio.index = MAX_INDEX;				
			mp3PlayerDemo(MP3_file[audio.index]);
		}
		
		
		audio.HP_status = HEAD_PHONE_DET?1:0;
		switch_player_device(audio.HP_status);
		
		if(Trim_info.lhl == 0)
		{
			volum_add_cnt ++;
			if(volum_add_cnt>5)//消除抖动
			{
				volum_add_cnt = 0;
				audio.Volume +=1;
				audio.Dis_Volume = 127 - audio.Volume;
				if(audio.Volume>127)
				{
					audio.Volume = 127;
				}
				if(audio.HP_status == USE_HP)
				{
					setting_volume_HP(audio.Volume);
				}
				else
				{
					setting_volume_SPK(audio.Volume);
				}
				
								
			}
		}
		else 
		{
			volum_add_cnt = 0;
			
		}
		if(Trim_info.lhr == 0) //按下
		{
			volum_dis_cnt ++;
			if(volum_dis_cnt>5)//消除抖动
			{
				volum_dis_cnt = 0;
				audio.Volume-=1;
				audio.Dis_Volume = 127 - audio.Volume;
				if(audio.Volume<1)
					audio.Volume = 0;
				if(audio.HP_status == USE_HP)
				{
					setting_volume_HP(audio.Volume);
				}
				else
				{
					setting_volume_SPK(audio.Volume);
				}
			}
			
		}
		else //松开手
		{

			volum_dis_cnt = 0;
		}

		tas2505_tick = HAL_GetTick();
	}
}


uint8_t temp_buf[8] ={0};

// 初始化 TAS2505
void TAS2505_Init(void)
{
    tas2505_gpio_init();
	MX_I2S2_Init();
	
	I2S_Stop();
	I2S_GPIO_Config();
	I2Sx_Mode_Config(I2S_STANDARD_PHILIPS,I2S_DATAFORMAT_16B,mp3player.ucFreq);	
	I2Sx_TX_DMA_Init();	
	
    TAS2505_RST_Set(0);
    HAL_Delay(2);
    TAS2505_RST_Set(1);
    // 切换到页面 0
    TAS2505_WriteRegister(0x00, 0x00);
    
    // 软件复位
    TAS2505_WriteRegister(0x01, 0x01);
/****************以下在页面 1************************************/        
    // 切换到页面 1
    TAS2505_WriteRegister(0x00, 0x01);
    
    // LDO 输出设置为 1.8V，电平转换器供电
    TAS2505_WriteRegister(0x02, 0x00);
/****************以下在页面 0************************************/        
    // 切换回页面 0
    TAS2505_WriteRegister(0x00, 0x00);
    
    // // PLL_clkin = MCLK, codec_clkin = PLL_CLK，MCLK 应为 11.2896MHz
//    TAS2505_WriteRegister(0x04, 0x03); 
    //高频，PLL_clkin = MCLK, codec_clkin = MCLK
//    TAS2505_WriteRegister(0x04, 0x40);  
    //低频，PLL_clkin = MCLK, codec_clkin = MCLK
    TAS2505_WriteRegister(0x04, 0x00);  

    // 使能 PLL，上电
    TAS2505_WriteRegister(0x05, 0x91);
    
    // 设置 J=4
    TAS2505_WriteRegister(0x06, 0x04);
    
    // D = 0000
    TAS2505_WriteRegister(0x07, 0x00);
    
    // D(7:0) = 0
    TAS2505_WriteRegister(0x08, 0x00);
    
    // 添加 15 ms 延迟以便 PLL 锁定
    HAL_Delay(15);

    // DAC NDAC 上电，NDAC=4
//    TAS2505_WriteRegister(0x0B, 0x84);
	//NDAC=4
    TAS2505_WriteRegister(0x0B, 0x82); //2
	
    // DAC MDAC 上电，MDAC=2
//    TAS2505_WriteRegister(0x0C, 0x82);
    TAS2505_WriteRegister(0x0C, 0x81); //01
    // DAC OSR(9:8)-> DOSR=128
    TAS2505_WriteRegister(0x0D, 0x00); //OSR是十位，所以这里填00
    
//    // DAC OSR(7:0)-> DOSR=128
//    TAS2505_WriteRegister(0x0E, 0x80);
    // DAC OSR(7:0)-> DOSR=64
    TAS2505_WriteRegister(0x0E, 0x40);

    // I2S 模式,音频数据控制字长 = 16 位,BCLK&WCLK 输入到器件
    TAS2505_WriteRegister(0x1B, 0x00);
    
    // 数据插槽偏移 00
    TAS2505_WriteRegister(0x1C, 0x00);
    
    // DAC 指令编程 PRB #2，单声道路由，类型插值 (x8) 和 3 个可编程的 Biquads
    TAS2505_WriteRegister(0x3C, 0x02);
	
/****************以下在页面 0************************************/      
    // 切换回页面 0
    TAS2505_WriteRegister(0x00, 0x00);
    
    // DAC 上电，软启动每 Fs 1
//    TAS2505_WriteRegister(0x3F, 0x90);
    TAS2505_WriteRegister(0x3F, 0xB0);   //DAC 数据来自左右声道音频接口数据的单声道混合 

    // DAC 数字增益 0dB
    TAS2505_WriteRegister(0x41, 0x00);
    // DAC 音量不静音
    TAS2505_WriteRegister(0x40, 0x04);
/****************以下在页面 1************************************/    
    // 切换到页面 1
    TAS2505_WriteRegister(0x00, 0x01);
    
    // 参考电源打开
    TAS2505_WriteRegister(0x01, 0x10);  

    // 上电 HP
    TAS2505_WriteRegister(0x09, 0x20);
	
    // DAC 的共模输出设置为 0.9V (默认)
    TAS2505_WriteRegister(0x0A, 0x00);
    
    // Mixer P 输出连接到 HP 输出 Mixer
    TAS2505_WriteRegister(0x0C, 0x04);
//     TAS2505_WriteRegister(0x0C, 0x08);

    // 取消静音 HP，0dB 增益
    TAS2505_WriteRegister(0x10, 0x00);

    // HP 音量
//    TAS2505_WriteRegister(0x16, 0x20);//衰减系数，数值越大，声音越小
	TAS2505_WriteRegister(0x16, audio.Volume);
    // 不需要使能 Mixer M 和 Mixer P，AINL 音量，0dB 增益
    TAS2505_WriteRegister(0x18, 0x00);

    // SPK 衰减增益 = 0dB
//    TAS2505_WriteRegister(0x2E, 0x01);//衰减系数，数值越大，声音越小
   TAS2505_WriteRegister(0x2E, audio.Volume);

    // SPK 驱动增益 = 32dB
    TAS2505_WriteRegister(0x30, 0x50); //SPK 驱动器音量 = 32dB

    // SPK 上电
    TAS2505_WriteRegister(0x2D, 0x02);        
	
}

void setting_volume_HP(uint8_t volume)
{
	
    TAS2505_WriteRegister(0x00, 0x01);
	
    volume = (volume>116)?116:volume;
	
    TAS2505_WriteRegister(0x16, volume);
    
}

void setting_volume_SPK(uint8_t volume)
{
    TAS2505_WriteRegister(0x00, 0x01);
    
	volume = (volume>116)?116:volume;
    TAS2505_WriteRegister(0x2E, volume);

}

void setting_max_volume_SPK(void)
{
    TAS2505_WriteRegister(0x00, 0x01);
    
    TAS2505_WriteRegister(0x2E, 0);
	TAS2505_WriteRegister(0x30, 0x50); //SPK 驱动器音量 = 32dB
}

//耳机口插入就关闭扬声器，开启耳机电源

void switch_player_device(uint8_t dev)
{
	TAS2505_WriteRegister(0x00, 0x01);
	if(dev == USE_SPK)
	{		
		// SPK 上电
		TAS2505_WriteRegister(0x2D, 0x02); 
		// HP 关电
		TAS2505_WriteRegister(0x09, 0x00);	
	}		
	else
	{
		// 上电 HP
		TAS2505_WriteRegister(0x09, 0x20);
		// SPK 关电
		TAS2505_WriteRegister(0x2D, 0x00);		


	}
}

void MusicPlayer_I2S_DMA_TX_Callback(void)
{
	bufflag=(I2Sx_TX_DMA_STREAM->CR&(1<<19)) ? 0 : 1;
	Isread=1;
}
