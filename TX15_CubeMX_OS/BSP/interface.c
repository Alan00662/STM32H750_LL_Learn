#include "interface.h"
#include "bsp_tas2505.h"
#include "bsp_rtc.h"
#include "bsp_icm42607.h"
uint32_t adc_s1 = 0;
uint32_t adc_s2 = 0;
uint32_t adc_bat = 0;
float Vbat =0.0;

uint32_t adc_scan_tick = 0;
void ADC_scan_Loop(void)
{
	if((HAL_GetTick() - adc_scan_tick) > 6)
	{
		adc_bat = adc3_get_result_average1(ADC_BAT_CH,10);
		adc_s2 = adc1_get_result_average1(ADC_S2_CH,10);
		adc_s1 = adc1_get_result_average1(ADC_S1_CH,10);
		Vbat = (float)(adc_bat*3.3/4096.0) * ((160+499)/160);
        adc_scan_tick = HAL_GetTick();
	}
}

uint32_t tft_display_tick = 0;
void Menu_Display_Loop(void)
{
//	char str1[300] ={0};
//	char str2[300] ={0};
	if((HAL_GetTick() - tft_display_tick) > 3)
	{

	TFT_show_string(100,0,260,"RadioMaster_TX15",TFT_FONT_32,BLUE); 
	TFT_show_string(0,32,80,"Backlght:",TFT_FONT_16,RED); 
	TFT_show_num(90,32,backlight_pwm,3,TFT_FONT_16,RED);
	TFT_show_char(120, 32, '%', TFT_FONT_16, RED);
		
	TFT_show_string(150,32,70,"adc_bat:",TFT_FONT_16,RED);
	TFT_show_num(230,32,adc_bat,5,TFT_FONT_16,RED);
		
//	TFT_show_num(300,32,Vbat*100,4,TFT_FONT_16,RED);
	TFT_show_flaot_num(300,32,Vbat,4,RED);	

		
	TFT_show_string(0,50,64,"key_SYS:",TFT_FONT_16,RED); 
	TFT_show_num(64,50,Key_info.sys,1,TFT_FONT_16,RED);		
	TFT_show_string(96,50,64,"key_MDL:",TFT_FONT_16,RED); 
	TFT_show_num(160,50,Key_info.modle,1,TFT_FONT_16,RED);			
	TFT_show_string(192,50,64,"key_RTN:",TFT_FONT_16,RED); 
	TFT_show_num(256,50,Key_info.rtn,1,TFT_FONT_16,RED);	
	TFT_show_string(288,50,64,"key_>>:",TFT_FONT_16,RED); 
	TFT_show_num(352,50,Key_info.right,1,TFT_FONT_16,RED);	
	TFT_show_string(384,50,64,"key_<<:",TFT_FONT_16,RED); 
	TFT_show_num(448,50,Key_info.left,1,TFT_FONT_16,RED);
	TFT_show_string(0,70,64,"key_TEL:",TFT_FONT_16,RED); 
	TFT_show_num(64,70,Key_info.tele,1,TFT_FONT_16,RED);
	TFT_show_string(96,70,64,"key_ENT:",TFT_FONT_16,RED); 
	TFT_show_num(160,70,Key_info.enter,1,TFT_FONT_16,RED);
		
	TFT_show_string(192,70,64,"T2_u:",TFT_FONT_16,BLACK); 
	TFT_show_num(246,70,Trim_info.rvu,1,TFT_FONT_16,BLACK);
	TFT_show_string(288,70,64,"T2_d:",TFT_FONT_16,BLACK); 
	TFT_show_num(342,70,Trim_info.rvd,1,TFT_FONT_16,BLACK);
	TFT_show_string(384,70,64,"T1_r:",TFT_FONT_16,BLACK); 
	TFT_show_num(438,70,Trim_info.rhr,1,TFT_FONT_16,BLACK);	
	
	TFT_show_string(0,90,64,"T1_l:",TFT_FONT_16,BLACK); 
	TFT_show_num(54,90,Trim_info.rhl,1,TFT_FONT_16,BLACK);
	TFT_show_string(96,90,64,"T3_u:",TFT_FONT_16,BLACK); 
	TFT_show_num(150,90,Trim_info.lvu,1,TFT_FONT_16,BLACK);
	TFT_show_string(192,90,64,"T3_d:",TFT_FONT_16,BLACK); 
	TFT_show_num(246,90,Trim_info.lvd,1,TFT_FONT_16,BLACK);
	TFT_show_string(288,90,64,"T4_r:",TFT_FONT_16,BLACK); 
	TFT_show_num(342,90,Trim_info.lhr,1,TFT_FONT_16,BLACK);
	TFT_show_string(384,90,72,"T4_l:",TFT_FONT_16,BLACK); 
	TFT_show_num(438,90,Trim_info.lhl,1,TFT_FONT_16,BLACK);	

	TFT_show_string(0,110,70,"Encoder:",TFT_FONT_16,BLUE); 
	TFT_show_negative_num(80,110,Encoder,4,BLUE);

	TFT_show_string(192,110,70,"adc_S1:",TFT_FONT_16,BLUE); 
	TFT_show_num(256,110,adc_s1,4,TFT_FONT_16,BLUE);
	TFT_show_string(320,110,70,"adc_S2:",TFT_FONT_16,BLUE); 
	TFT_show_num(390,110,adc_s2,4,TFT_FONT_16,BLUE);

	TFT_show_string(0,130,30,"k1:",TFT_FONT_16,BROWN); 
	TFT_show_num(30,130,Tca9539.k1,1,TFT_FONT_16,BROWN);
	
	TFT_show_string(64,130,30,"k2:",TFT_FONT_16,BROWN); 
	TFT_show_num(94,130,Tca9539.k2,1,TFT_FONT_16,BROWN);
	
	TFT_show_string(128,130,30,"k3:",TFT_FONT_16,BROWN); 
	TFT_show_num(158,130,Tca9539.k3,1,TFT_FONT_16,BROWN);
	
	TFT_show_string(192,130,30,"k4:",TFT_FONT_16,BROWN); 
	TFT_show_num(222,130,Tca9539.k4,1,TFT_FONT_16,BROWN);
	
	TFT_show_string(256,130,30,"k5:",TFT_FONT_16,BROWN); 
	TFT_show_num(286,130,Tca9539.k5,1,TFT_FONT_16,BROWN);
	
	TFT_show_string(320,130,30,"k6:",TFT_FONT_16,BROWN); 
	TFT_show_num(350,130,Tca9539.k6,1,TFT_FONT_16,BROWN);

	TFT_show_string(0,150,30,"SA:",TFT_FONT_16,DARKBLUE); 
	TFT_show_num(30,150,Tca9539_sw.SA,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(64,150,30,"SB:",TFT_FONT_16,DARKBLUE); 
	TFT_show_num(94,150,Tca9539_sw.SB,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(128,150,30,"SC:",TFT_FONT_16,DARKBLUE); 
	TFT_show_num(158,150,Tca9539_sw.SC,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(192,150,30,"SD:",TFT_FONT_16,DARKBLUE); 
	TFT_show_num(222,150,Tca9539_sw.SD,1,TFT_FONT_16,DARKBLUE);

	TFT_show_string(256,150,30,"SE:",TFT_FONT_16,DARKBLUE); 
	TFT_show_num(286,150,Tca9539_sw.SE,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(320,150,30,"SF:",TFT_FONT_16,DARKBLUE); 
	TFT_show_num(350,150,Tca9539_sw.SF,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(0,170,30,"X1:",TFT_FONT_16,BLACK); 
	TFT_show_negative_num(40,170,Stick.X1,4,BLACK);
	TFT_show_string(88,170,30,"Y1:",TFT_FONT_16,BLACK); 
	TFT_show_negative_num(128,170,Stick.Y1,4,BLACK);
	TFT_show_string(176,170,30,"X2:",TFT_FONT_16,BLACK); 
	TFT_show_negative_num(216,170,Stick.X2,4,BLACK);
	TFT_show_string(264,170,30,"Y2:",TFT_FONT_16,BLACK); 
	TFT_show_negative_num(304,170,Stick.Y2,4,BLACK);

	TFT_show_string(0,190,70,"Touch_X:",TFT_FONT_16,RED); 
	TFT_show_num(70,190,Touch_X,3,TFT_FONT_16,RED);
	TFT_show_string(110,190,70,"Touch_Y:",TFT_FONT_16,RED);
	TFT_show_num(180,190,Touch_Y,3,TFT_FONT_16,RED);
	
	TFT_show_string(220,190,70,"SD_sta:",TFT_FONT_16,BLACK);
	TFT_show_num(280,190,sd_sta,1,TFT_FONT_16,BLACK);	

//	TFT_show_string(310,190,70,"PH_sta:",TFT_FONT_16,BLACK);
//	TFT_show_num(380,190,audio.HP_status,1,TFT_FONT_16,BLACK);	
//	
//	TFT_show_string(0,210,70,"MP3_sta:",TFT_FONT_16,BLACK); 
//	TFT_show_num(80,210,mp3player.ucStatus,1,TFT_FONT_16,BLACK);

//	TFT_show_string(100,210,100,"Current_MP3:",TFT_FONT_16,BLACK);
//	lcd_show_mp3_name(210,210,150,MP3_file[audio.index],BLUE);
//	
//		TFT_show_string(340,210,70,"Volume:",TFT_FONT_16,RED);
//		TFT_show_num(410,210,audio.Dis_Volume,3,TFT_FONT_16,RED);	
//	TFT_show_string(220,210,150,MP3_file[audio.index],TFT_FONT_16,BLACK);
	
		TFT_show_string(0,230,40,"RTC:",TFT_FONT_16,RED);
		
		TFT_show_num(40,230,2000+DisRtc.Year,4,TFT_FONT_16,BLACK);	
	  TFT_show_char(80, 230, '-', TFT_FONT_16, BLACK);
		TFT_show_num(96,230,DisRtc.Month,2,TFT_FONT_16,BLACK);	
	  TFT_show_char(122, 230, '-', TFT_FONT_16, BLACK);
		TFT_show_num(138,230,DisRtc.Date,2,TFT_FONT_16,BLACK);	
		
	  TFT_show_num(210,230,DisRtc.Hours,2,TFT_FONT_16,BLACK);	
	  TFT_show_char(232, 230, ':', TFT_FONT_16, BLACK);
		TFT_show_num(248,230,DisRtc.Minutes,2,TFT_FONT_16,BLACK);	
	  TFT_show_char(270, 230, ':', TFT_FONT_16, BLACK);
		TFT_show_num(286,230,DisRtc.Seconds,2,TFT_FONT_16,BLACK);	
		
		TFT_show_string(0,250,50,"accX:",TFT_FONT_16,BLACK);
		TFT_show_num(50,250,IMU.acc[0],5,TFT_FONT_16,BLACK);	
		
		TFT_show_string(100,250,50,"accY:",TFT_FONT_16,BLACK); 
		TFT_show_num(150,250,IMU.acc[1],5,TFT_FONT_16,BLACK);	
		
		TFT_show_string(200,250,50,"accZ:",TFT_FONT_16,BLACK); 
		TFT_show_num(250,250,IMU.acc[2],5,TFT_FONT_16,BLACK);	
		
		TFT_show_string(0,270,60,"groyX:",TFT_FONT_16,BLACK); 
		TFT_show_num(60,270,IMU.gyro[0],5,TFT_FONT_16,BLACK);	
		
		TFT_show_string(120,270,60,"groyY:",TFT_FONT_16,BLACK); 
		TFT_show_num(180,270,IMU.gyro[1],5,TFT_FONT_16,BLACK);
		TFT_show_string(240,270,60,"groyZ:",TFT_FONT_16,BLACK); 
		TFT_show_num(300,270,IMU.gyro[2],5,TFT_FONT_16,BLACK);
//		sprintf(str1,"accX =%d,accY =%d,accZ =%d\n",IMU.acc[0],IMU.acc[1],IMU.acc[2]);
//		TFT_show_string(0,250,300,str1,TFT_FONT_16,BLACK); 
//		sprintf(str2,"groyX =%d,groyY =%d,groyZ =%d\n",IMU.groy[0],IMU.groy[1],IMU.groy[2]);
//		TFT_show_string(0,270,300,str2,TFT_FONT_16,BLACK); 
//	TFT_show_string(0,230,300,LCDDate,TFT_FONT_16,BLACK);
//	TFT_show_string(0,250,300,LCDTime,TFT_FONT_16,BLACK);		
		tft_display_tick =  HAL_GetTick();
	}

}	

uint32_t mp3_display_tick = 0;
void MP3_Menu_Display(void)
{

	if((HAL_GetTick() - mp3_display_tick) > 2)
	{
		TFT_show_string(140,0,260,"MP3 Play Mode",TFT_FONT_32,BLUE); 
		
		TFT_show_string(10,50,70,"PH_sta:",TFT_FONT_16,BLACK);
		TFT_show_num(80,50,audio.HP_status,1,TFT_FONT_16,BLACK);	
		
		TFT_show_string(350,50,70,"MP3_sta:",TFT_FONT_16,BLACK); 
		TFT_show_num(430,50,mp3player.ucStatus,1,TFT_FONT_16,BLACK);
		
		TFT_show_string(50,110,100,"Current_MP3:",TFT_FONT_16,BLACK);
		lcd_show_mp3_name(210,110,150,MP3_file[audio.index],BLUE);
	
		TFT_show_string(340,110,70,"Volume:",TFT_FONT_16,RED);
		TFT_show_num(410,110,audio.Dis_Volume,3,TFT_FONT_16,RED);	
		
		mp3_display_tick = HAL_GetTick();
	}
}

void color_test(void)
{
	TFT_show_string(0,0,100,"WHITE",TFT_FONT_32,WHITE);	
	TFT_show_string(100,0,100,"BLACK",TFT_FONT_32,BLACK); 
	TFT_show_string(200,0,100,"RED",TFT_FONT_32,RED); 
	TFT_show_string(300,0,100,"GREEN",TFT_FONT_32,GREEN);
	TFT_show_string(400,0,80,"BLUE",TFT_FONT_32,BLUE); 	
	
	TFT_show_string(0,35,120,"MAGENTA",TFT_FONT_32,MAGENTA); 
	TFT_show_string(120,35,100,"YELLOW",TFT_FONT_32,YELLOW); 
	TFT_show_string(230,35,100,"CYAN",TFT_FONT_32,CYAN); 
	TFT_show_string(320,35,100,"BROWN",TFT_FONT_32,BROWN);
	
	TFT_show_string(0,70,100,"BRRED",TFT_FONT_32,BRRED);	
	TFT_show_string(100,70,80,"GRAY",TFT_FONT_32,GRAY); 
	TFT_show_string(180,70,130,"DARKBLUE",TFT_FONT_32,DARKBLUE); 
	TFT_show_string(325,70,150,"LIGHTBLUE",TFT_FONT_32,LIGHTBLUE); 
	TFT_show_string(0,105,150,"GRAYBLUE",TFT_FONT_32,GRAYBLUE);
	
	TFT_show_string(150,105,200,"LIGHTGREEN",TFT_FONT_32,LIGHTGREEN);	
	TFT_show_string(350,105,100,"LGRAY",TFT_FONT_32,LGRAY); 
	
	TFT_show_string(0,145,150,"LGRAYBLUE",TFT_FONT_32,LGRAYBLUE); 
	TFT_show_string(150,145,120,"LBBLUE",TFT_FONT_32,LBBLUE);
}

	