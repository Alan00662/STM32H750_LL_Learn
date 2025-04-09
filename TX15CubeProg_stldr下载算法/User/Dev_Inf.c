#include "Dev_Inf.h"


#if defined (__ICCARM__)
__root struct StorageInfo const StorageInfo  =  {
#else
struct StorageInfo const StorageInfo =  {
#endif
    "TX15_W25Q128", /* 算法名，添加算法到STM32CubeProg安装目录会显示此名字 */
    NOR_FLASH,                      /* 设备类型 */
    0x90000000,                     /* Flash起始地址 */
    16 * 1024 * 1024,               /* Flash大小，16MB */
    4*1024,                         /* 编程页大小 */
    0xFF,                           /* 擦除后的数值 */
    256 , 											/*256*64*1024 = 16 * 1024 * 1024*/
	  64 * 1024,                /* 块个数和块大小 */
    0x00000000, 0x00000000,
};


