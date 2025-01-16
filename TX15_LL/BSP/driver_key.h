#ifndef __DRIVER_KEY_H__
#define __DRIVER_KEY_H__

#include "main.h"

enum EnumKeys {
  KEY_MENU,
  KEY_EXIT,
  KEY_ENTER,

  KEY_PAGEUP,
  KEY_PAGEDN,

  KEY_UP,
  KEY_DOWN,

  KEY_LEFT,
  KEY_RIGHT,

  KEY_PLUS,
  KEY_MINUS,

  KEY_MODEL,
  KEY_TELE,
  KEY_SYS,

  KEY_SHIFT,
  KEY_BIND,

  MAX_KEYS
};

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
void readKeys(void);
#endif

