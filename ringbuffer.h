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

typedef unsigned char uint8_t;

#define __DEBUG__

#ifdef      __cplusplus
extern "C"{
#endif


/* 定义长度为2的幂次 */
#define     RINGBUFFER_SIZE     0x10U    /* 缓冲区大小定义 */
#define     SINGLE_BUFFER       0x08U    /* CAN报文缓冲大小 */

typedef struct
{
    
    uint8_t     *buf;

    uint8_t     size;
    
    uint8_t     start;
    
    uint8_t     end;

#ifdef  __DEBUG__
    uint8_t     Txlen;

    uint8_t     Rxlen;
#endif

}ringbuffer;


extern uint8_t ringbufferArray[RINGBUFFER_SIZE][SINGLE_BUFFER];


void ringbuffer_Init(ringbuffer *rb);
void ringbuffer_write(ringbuffer *rb , uint8_t *data);
uint8_t *ringbuffer_read(ringbuffer *rb);

#ifdef      __cplusplus
}
#endif

#endif

/*************************** vccw (END OF FILE)*********************************************************/    