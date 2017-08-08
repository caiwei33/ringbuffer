/*
*********************************************************************************************************
*
*	模块名称 : 环形缓冲区
*	文件名称 : ringbuffer.h
*	版    本 : V1.0
*	说    明 :
*	修改记录 :
*		版本号   日期       作者     说明
*		v1.0    2017-07-11  vccw     首发
*
*
*
*	Copyright (C), 2017  vccw
*
*********************************************************************************************************
*/

#ifndef     __RINGBUFFER_H
#define     __RINGBUFFER_H



#ifdef      __cplusplus
extern "C"{
#endif

#ifndef __GNUC__
#include "PE_Types.h"
#else
#include "stdint.h"
#endif


#define     __DEBUG__

/* 定义长度为2的幂次 */
#define     RINGBUFFER_SIZE     0x10U    /* 缓冲区大小定义 */
#define     SINGLE_BUFFER       0x08U    /* CAN报文缓冲大小 */

typedef struct
{
    uint8_t     Type;

    uint8_t     (*databuf)[8];

    uint32_t    *idbuf;

    uint8_t     size;

    uint8_t     start;

    uint8_t     end;
	
	uint8_t     isFull;
	
	uint8_t     isEmpty;

#ifdef  __DEBUG__
    uint8_t     Txlen;

    uint8_t     Rxlen;
#endif

}ringbuffer;


typedef struct
{
    uint8_t     *data;

    uint32_t     *id;

}ringbuffer_cangroup;



extern uint8_t ringbufferArray[RINGBUFFER_SIZE][SINGLE_BUFFER];


void ringbuffer_Init(ringbuffer *rb);
void ringbuffer_write(ringbuffer *rb , uint8_t *data , uint32_t id, uint8_t slen);
ringbuffer_cangroup ringbuffer_read(ringbuffer *rb);

#ifdef      __cplusplus
}
#endif

#endif

/*************************** vccw (END OF FILE)*********************************************************/
