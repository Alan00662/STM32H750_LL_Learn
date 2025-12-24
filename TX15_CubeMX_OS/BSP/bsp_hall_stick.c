
#include "usart.h"
#include "bsp_hall_stick.h"
#include "fifo.h"
#define OPEN_CONTUI 	1
uint8_t read_joystick[8] = {0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41};
uint8_t Rx_joystick[12] = {0};
uint8_t rx4_sta = 0;
uint8_t step = 0;
uint16_t crc1 = 0;
uint16_t crc2 = 0;
hall_stick_t Stick;
STRUCT_HALL HallProtocol = { 0 };
static const unsigned short crc16tab_1021[256] = {
  0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
  0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
  0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
  0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
  0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
  0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
  0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
  0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
  0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
  0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
  0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
  0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
  0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
  0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
  0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
  0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
  0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
  0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
  0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
  0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
  0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
  0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
  0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
  0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
  0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
  0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
  0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
  0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
  0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
  0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
  0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
  0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};


const unsigned short * const crc16tab[] = {
  crc16tab_1021
};


static uint16_t crc16(uint8_t index, const uint8_t * buf, uint32_t len, uint16_t start)
{
  uint16_t crc = start;
  const unsigned short * tab = crc16tab[index];
  for (uint32_t i = 0; i < len; i++) {
    crc = (crc << 8) ^ tab[((crc >> 8) ^ *buf++) & 0x00FF];
  }
  return crc;
}
/**
 * @brief  Convert the data to signed data.
 */
static int16_t convert_to_signed(uint8_t data_H, uint8_t data_L)
{
    int16_t data = 0;
    data = (data_H << 8) | data_L;
    if(data & 0x8000)
    {
        data = data - 0x10000;

    }
    return -data;
}


static void _fs_parse(STRUCT_HALL *hallBuffer, unsigned char ch)
{
    switch (hallBuffer->status)
    {
    case GET_START:
        if (FLYSKY_HALL_PROTOLO_HEAD == ch)
        {
            hallBuffer->head = FLYSKY_HALL_PROTOLO_HEAD;
            hallBuffer->status = GET_ID;
            hallBuffer->msg_OK = 0;
        }
        break;

    case GET_ID:
        hallBuffer->hallID.ID = ch;
        hallBuffer->status = GET_LENGTH;
        break;

    case GET_LENGTH:
        hallBuffer->length = ch;
        hallBuffer->dataIndex = 0;
        hallBuffer->status = GET_DATA;
        if (0 == hallBuffer->length)
        {
            hallBuffer->status = GET_CHECKSUM;
            hallBuffer->checkSum = 0;
        }
        break;

    case GET_DATA:
        hallBuffer->data[hallBuffer->dataIndex++] = ch;
        if (hallBuffer->dataIndex >= hallBuffer->length)
        {
            hallBuffer->checkSum = 0;
            hallBuffer->dataIndex = 0;
            hallBuffer->status = GET_STATE;
        }
        break;

    case GET_STATE:
        hallBuffer->checkSum = 0;
        hallBuffer->dataIndex = 0;
        hallBuffer->status = GET_CHECKSUM;
        // fall through!

    case GET_CHECKSUM:
        hallBuffer->checkSum |= ch << ((hallBuffer->dataIndex++) * 8);
        if (hallBuffer->dataIndex >= 2)
        {
            hallBuffer->dataIndex = 0;
            hallBuffer->status = CHECKSUM;
            // fall through!
        }
        else
        {
            break;
        }

    case CHECKSUM:
        if (hallBuffer->checkSum ==
            crc16(0, &hallBuffer->head, hallBuffer->length + 3, 0xffff))
        {
            hallBuffer->msg_OK = 1;

            Stick.X1 = convert_to_signed(hallBuffer->data[1], hallBuffer->data[0]);
            Stick.Y1 = convert_to_signed(hallBuffer->data[3], hallBuffer->data[2]);
            Stick.Y2 = convert_to_signed(hallBuffer->data[5], hallBuffer->data[4]);
            Stick.X2 = convert_to_signed(hallBuffer->data[7], hallBuffer->data[6]);

        }
        hallBuffer->status = GET_START;
        break;
    }
}




static void rx4_data_in(uint8_t data)
{

    switch (step)
    {

    case 0:
        if (data == 0x55) //HEAD
        {
            Stick.Hall_buf[0] = data;
            rx4_sta = 0 ;
            step = 1;
        }
        break;
    case 1:
        if (data == 0xC4) //ID
        {
            Stick.Hall_buf[1] = data;
            rx4_sta = 1 ;
            step = 2;
        }
        break;
	case 2:
        if (data == 0x09) //length
        {
            Stick.Hall_buf[2] = data;
            rx4_sta = 2 ;
            step = 3;
        }
        break;
    case 3:
        if (Stick.Hall_buf[0] == 0x55 && Stick.Hall_buf[1] == 0xC4 && Stick.Hall_buf[2] == 0x09)
        {
            Stick.Hall_buf[rx4_sta+1 ] = data;
            rx4_sta++;

            if (rx4_sta > 12 /*&& Stick.Hall_buf[11] == 0x11*/)
            {

                Stick.X1 = convert_to_signed(Stick.Hall_buf[4],Stick.Hall_buf[3]);
                Stick.Y1 = convert_to_signed(Stick.Hall_buf[6],Stick.Hall_buf[5]);
                Stick.Y2 = convert_to_signed(Stick.Hall_buf[8],Stick.Hall_buf[7]);
                Stick.X2 = convert_to_signed(Stick.Hall_buf[10],Stick.Hall_buf[9]);
                rx4_sta = 0;
                step = 0;

            }
        }

        break;
    }
//}
}

uint8_t hall_data = 0;
uint32_t hall_stick_tick = 0;
void Hall_stick_Loop(void)
{

//	if ((HAL_GetTick() - hall_stick_tick) >= 3)
//    {
#if !UART4_USE_FIFO //持续发送，摇杆一直往单片机吐数据
    HAL_UART_Receive(&huart4, (uint8_t *)g_rx_buffer, sizeof(g_rx_buffer), 50);
//	
    rx4_data_in(g_rx_buffer[0]);

//	HallProtocol.index++;
//	_fs_parse(&HallProtocol,g_rx_buffer[0]);
//	    if (HallProtocol.msg_OK) {
//      HallProtocol.msg_OK = 0;
//      HallProtocol.stickState = HallProtocol.data[HallProtocol.length - 1];

//		}
#else 

	pop_one_fifo(&fifo_gimbal, &hall_data);

    HallProtocol.index++;

    _fs_parse(&HallProtocol, hall_data);
    if (HallProtocol.msg_OK)
    {
        HallProtocol.msg_OK = 0;
        HallProtocol.stickState = HallProtocol.data[HallProtocol.length - 1];
    }

#endif
//        hall_stick_tick = HAL_GetTick();
//    }
}
