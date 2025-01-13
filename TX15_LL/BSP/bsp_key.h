
#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define PWR_KEY_Pin 		LL_GPIO_PIN_4
#define PWR_KEY_GPIO_Port 	GPIOA

#define ENTER_Pin 			LL_GPIO_PIN_12
#define ENTER_GPIO_Port 	GPIOG

#define MDL_Pin 			LL_GPIO_PIN_3
#define MDL_GPIO_Port 		GPIOE

#define PAGE_L_Pin 			LL_GPIO_PIN_7
#define PAGE_L_GPIO_Port 	GPIOG

#define PAGE_R_Pin 			LL_GPIO_PIN_8
#define PAGE_R_GPIO_Port 	GPIOA

#define RTN_Pin 			LL_GPIO_PIN_3
#define RTN_GPIO_Port 		GPIOG

#define TELE_Pin 			LL_GPIO_PIN_2
#define TELE_GPIO_Port 		GPIOG

#define SYS_Pin 			LL_GPIO_PIN_2
#define SYS_GPIO_Port 		GPIOB

#define KEY_PAGE_L 			LL_GPIO_IsInputPinSet(PAGE_L_GPIO_Port, PAGE_L_Pin)
#define KEY_PAGE_R 			LL_GPIO_IsInputPinSet(PAGE_R_GPIO_Port, PAGE_R_Pin)
#define KEY_MDL 			LL_GPIO_IsInputPinSet(MDL_GPIO_Port, MDL_Pin)
#define KEY_TELE 			LL_GPIO_IsInputPinSet(TELE_GPIO_Port, TELE_Pin)
#define KEY_SYS 			LL_GPIO_IsInputPinSet(SYS_GPIO_Port, SYS_Pin)
#define KEY_RTN 			LL_GPIO_IsInputPinSet(RTN_GPIO_Port, RTN_Pin)
#define KEY_ENTER 			LL_GPIO_IsInputPinSet(ENTER_GPIO_Port, ENTER_Pin)
#define PWR_SWITCH 			LL_GPIO_IsInputPinSet(PWR_KEY_GPIO_Port, PWR_KEY_Pin)

#define SCAN_TIMEOUT  		10


/* 键值定义 */
enum
{
    NONE_PRES = 0,
    SYS_PRES,            
    RTN_PRES,              
    RIGHT_PRES,            
    LEFT_PRES,             
    TELE_PRES, 
    MDL_PRES,               
    ENTER_PRES          
 
};
          

typedef struct key_info
{
    uint8_t left;  /* data */
    uint8_t right; /* data */
    uint8_t sys;   /* data */
    uint8_t modle; /* data */
    uint8_t enter; /* data */
    uint8_t tele;  /* data */
    uint8_t rtn;   /* data */
} key_info_t;
extern key_info_t Key_info;



void KEY_GPIO_init(void);
void key_scan_Loop(void);
void trim_scan_Loop(void);
void switch_scan_Loop(void);
#ifdef __cplusplus
}
#endif

#endif
