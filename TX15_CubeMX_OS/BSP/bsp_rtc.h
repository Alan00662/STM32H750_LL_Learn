#ifndef __RTC_H__
#define __RTC_H__

#include "main.h"

extern RTC_HandleTypeDef Rtc_Handle;
// 时钟源宏定义
#define RTC_CLOCK_SOURCE_LSE      
//#define RTC_CLOCK_SOURCE_LSI  

// 异步分频因子
#define ASYNCHPREDIV         0X7F
// 同步分频因子
#define SYNCHPREDIV          0XFF

// 时间宏定义
#define RTC_H12_AMorPM			  RTC_HOURFORMAT12_AM  
#define HOURS                     12          // 0~23
#define MINUTES                   1          // 0~59
#define SECONDS                   1          // 0~59

// 日期宏定义
#define WEEKDAY                   4         // 1~7
#define DATE                      6         // 1~31
#define MONTH                     3         // 1~12
#define YEAR                      25//1         // 2000+0~99

// 时间格式宏定义
#define RTC_Format_BINorBCD  RTC_FORMAT_BIN

// 备份域寄存器宏定义
#define RTC_BKP_DRX          RTC_BKP_DR0
// 写入到备份寄存器的数据宏定义
#define RTC_BKP_DATA         0X32F2 

/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
	uint8_t Year;
	uint8_t Month;
	uint8_t Date;  
  uint8_t Hours;            
  uint8_t Minutes;                                     
  uint8_t Seconds;                                      
                                                                                         
} Rtc_Dis_TypeDef;
extern Rtc_Dis_TypeDef  DisRtc;
extern char LCDDate[100];
extern char LCDTime[100];
void RTC_CLK_Config(void);
void RTC_TimeAndDate_Set(void);
void RTC_TimeAndDate_Show(void);
void RTC_AlarmSet(void);

#endif // __RTC_H__
