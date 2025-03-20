/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "driver_delays.h"
#include "board.h"

#define SYSTEM_TICKS_1MS  ((CPU_FREQ + 500) / 1000)
#define SYSTEM_TICKS_1US  ((CPU_FREQ + 500000)  / 1000000)
#define SYSTEM_TICKS_01US ((CPU_FREQ + 5000000) / 10000000)

uint32_t ticksNow(void)
{
  return ((uint32_t)(DWT->CYCCNT));
}

void delaysInit(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

//0.1us
void delay_01us(uint32_t count)
{
  volatile uint32_t dwtStart = ticksNow();
  volatile uint32_t dwtTotal = (SYSTEM_TICKS_01US * count) - 10;
  while ((ticksNow() - dwtStart) < dwtTotal);
}

void delay_us(uint32_t count)
{
  volatile uint32_t dwtStart = ticksNow();
  volatile uint32_t dwtTotal = (SYSTEM_TICKS_1US * count) - 10;
  while ((ticksNow() - dwtStart) < dwtTotal);
}

void delay_1ms(void)
{
  volatile uint32_t dwtStart = ticksNow();
  volatile uint32_t dwtTotal = (SYSTEM_TICKS_1MS - 10)/2;
  while ((ticksNow() - dwtStart) < dwtTotal);
}

void delay_ms(uint32_t count)
{

  while (count--) {
    delay_1ms();
  }
}
