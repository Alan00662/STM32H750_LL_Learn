#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


void Debug_init(void);

void Debug(const char *fmt, ...);


#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

