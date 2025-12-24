#ifndef __HALL_STICK_H__
#define __HALL_STICK_H__

#include "main.h"
#define Hall_SIZE 14
enum {
  CRC_1021,
  CRC_1189,
};

#define HALLSTICK_BUFF_SIZE             ( 512 )
#define FLYSKY_HALL_PROTOLO_HEAD        0x55
#define FLYSKY_HALL_RESP_TYPE_VALUES    0x0c

typedef  struct
{
  signed short channel[4];
  unsigned char  stickState;
  unsigned short CRC16;
} STRUCT_CHANNEL_PACK;

typedef  struct
{
  unsigned char start;
  unsigned char senderID:2;
  unsigned char receiverID:2;
  unsigned char packetID:4;
  unsigned char length;
  STRUCT_CHANNEL_PACK payload;
} STRUCT_HALLDATA;

typedef  struct
{
  unsigned char senderID:2;
  unsigned char receiverID:2;
  unsigned char packetID:4;
} STRUCT_HALLID;

typedef union
{
  STRUCT_HALLID hall_Id;
  unsigned char ID;
} STRUCT_ID;


typedef union
{
  STRUCT_HALLDATA halldat;
  unsigned char buffer[30];
} UNION_HALLDATA;


typedef  struct
{
  unsigned char head;
  STRUCT_ID hallID;
  unsigned char length;
  unsigned char data[HALLSTICK_BUFF_SIZE];
  unsigned char reserved[15];
  unsigned short checkSum;
  unsigned char stickState;
  unsigned char startIndex;
  unsigned char endIndex;
  unsigned char index;
  unsigned char dataIndex;
  unsigned char deindex;
  unsigned char completeFlg;
  unsigned char status;
  unsigned char recevied;
  unsigned char msg_OK;
} STRUCT_HALL;

enum
{
  GET_START = 0,
  GET_ID,
  GET_LENGTH,
  GET_DATA,
  GET_STATE,
  GET_CHECKSUM,
  CHECKSUM,
};


typedef struct hall_stick_s
{
	uint8_t  Hall_buf[Hall_SIZE];
    int16_t X1;
    int16_t Y1;
    int16_t X2;
    int16_t Y2; /* data */
}__attribute__((packed)) hall_stick_t;

extern hall_stick_t Stick;

void Hall_stick_Loop(void);
#endif
