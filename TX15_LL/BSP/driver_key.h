#ifndef __DRIVER_KEY_H__
#define __DRIVER_KEY_H__

#include "main.h"

typedef enum  {
  KEY_EXIT,
  KEY_ENTER,

  KEY_PAGEUP,
  KEY_PAGEDN,

  KEY_MODEL,
  KEY_TELE,
  KEY_SYS,

  MAX_KEYS
}EnumKeys;

typedef struct key_info
{
    uint8_t left;  /* data */
    uint8_t right; /* data */
    uint8_t sys;   /* data */
    uint8_t mdl; /* data */
    uint8_t enter; /* data */
    uint8_t tele;  /* data */
    uint8_t exti;   /* data */
} key_info_t;
extern key_info_t Key;

void keysInit(void);
uint8_t readKeys(EnumKeys key);
#endif

