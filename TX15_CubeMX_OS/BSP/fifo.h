#include "main.h"

#define FIFO_MAX_LEN 1024
typedef struct
{
  uint16_t head;              	//队列头
	uint16_t tail;                //队列尾
	uint16_t len;                	//当前队列数据长度
	char buff[FIFO_MAX_LEN];  	//队列数组
}FIFO_TYPE;
extern FIFO_TYPE fifo;
extern FIFO_TYPE fifo_gimbal;
uint8_t pop_one_fifo(FIFO_TYPE* fifo,uint8_t* data);
uint8_t push_fifo(FIFO_TYPE* fifo,uint8_t* data,uint16_t len);
void pop_fifo(FIFO_TYPE* fifo,uint8_t* data,uint16_t len);

