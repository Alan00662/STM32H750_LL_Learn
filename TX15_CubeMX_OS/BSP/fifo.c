#include "FIFO.h"
#include "stdio.h"

FIFO_TYPE fifo = {0};

FIFO_TYPE fifo_gimbal = {0};

/*单个数据压入缓存*/
uint8_t push_one_fifo(FIFO_TYPE* fifo , uint8_t data)
{
	if(fifo->len < FIFO_MAX_LEN){
		fifo->buff[fifo->head]=data;		
		fifo->head=(fifo->head+1) % FIFO_MAX_LEN; 
		fifo->len++;
		return 1;
	}
	return 0;
}
 
/*缓存数据弹出*/
uint8_t pop_one_fifo(FIFO_TYPE* fifo,uint8_t* data)
{
	if(fifo->len > 0)						
	{
		*data = fifo->buff[fifo->tail];    /*取出一个字节数据*/
		/*头指针加1，到达最大值清零，构建环形队列*/
		fifo->tail=(fifo->tail+1) % FIFO_MAX_LEN;  
		fifo->len--;
		return 1;
	}		
	return 0;
}

/*多个数据压入*/
uint8_t push_fifo(FIFO_TYPE* fifo,uint8_t* data,uint16_t len)
{
	if((fifo->len + len) < FIFO_MAX_LEN)
	{
		for(int i=0;i<len;i++)
		{
			push_one_fifo(fifo , data[i]);
		}
		return 1;
	}
	return 0;
}

/*多个数据弹出*/
void pop_fifo(FIFO_TYPE* fifo,uint8_t* data, uint16_t len)
{
	for(int i=0;i<len;i++)
	{
		pop_one_fifo(fifo,&data[i]);
	}
}


