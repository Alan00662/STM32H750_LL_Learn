
#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define KEY_PAGE_L_GPIO_PORT GPIOG
#define KEY_PAGE_L_GPIO_PIN GPIO_PIN_7
#define KEY_PAGE_L_GPIO_CLK_ENABLE()  \
    do                                \
    {                                 \
        __HAL_RCC_GPIOG_CLK_ENABLE(); \
    } while (0)

#define KEY_PAGE_R_GPIO_PORT GPIOA
#define KEY_PAGE_R_GPIO_PIN GPIO_PIN_8
#define KEY_PAGE_R_GPIO_CLK_ENABLE()  \
    do                                \
    {                                 \
        __HAL_RCC_GPIOA_CLK_ENABLE(); \
    } while (0)

#define KEY_MDL_GPIO_PORT GPIOE
#define KEY_MDL_GPIO_PIN GPIO_PIN_3
#define KEY_MDL_GPIO_CLK_ENABLE()     \
    do                                \
    {                                 \
        __HAL_RCC_GPIOE_CLK_ENABLE(); \
    } while (0)

#define KEY_TELE_GPIO_PORT GPIOG
#define KEY_TELE_GPIO_PIN GPIO_PIN_2
#define KEY_TELE_GPIO_CLK_ENABLE()    \
    do                                \
    {                                 \
        __HAL_RCC_GPIOG_CLK_ENABLE(); \
    } while (0)

#define KEY_SYS_GPIO_PORT GPIOB
#define KEY_SYS_GPIO_PIN GPIO_PIN_2
#define KEY_SYS_GPIO_CLK_ENABLE()     \
    do                                \
    {                                 \
        __HAL_RCC_GPIOB_CLK_ENABLE(); \
    } while (0)

#define KEY_RTN_GPIO_PORT GPIOG
#define KEY_RTN_GPIO_PIN GPIO_PIN_3
#define KEY_RTN_GPIO_CLK_ENABLE()     \
    do                                \
    {                                 \
        __HAL_RCC_GPIOG_CLK_ENABLE(); \
    } while (0)

#define KEY_ENTER_GPIO_PORT GPIOG
#define KEY_ENTER_GPIO_PIN GPIO_PIN_12
#define KEY_ENTER_GPIO_CLK_ENABLE()   \
    do                                \
    {                                 \
        __HAL_RCC_GPIOG_CLK_ENABLE(); \
    } while (0)

#define KEY_PAGE_L HAL_GPIO_ReadPin(KEY_PAGE_L_GPIO_PORT, KEY_PAGE_L_GPIO_PIN)
#define KEY_PAGE_R HAL_GPIO_ReadPin(KEY_PAGE_R_GPIO_PORT, KEY_PAGE_R_GPIO_PIN)
#define KEY_MDL HAL_GPIO_ReadPin(KEY_MDL_GPIO_PORT, KEY_MDL_GPIO_PIN)
#define KEY_TELE HAL_GPIO_ReadPin(KEY_TELE_GPIO_PORT, KEY_TELE_GPIO_PIN)
#define KEY_SYS HAL_GPIO_ReadPin(KEY_SYS_GPIO_PORT, KEY_SYS_GPIO_PIN)
#define KEY_RTN HAL_GPIO_ReadPin(KEY_RTN_GPIO_PORT, KEY_RTN_GPIO_PIN)
#define KEY_ENTER HAL_GPIO_ReadPin(KEY_ENTER_GPIO_PORT, KEY_ENTER_GPIO_PIN)


#define SCAN_TIMEOUT  10


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
