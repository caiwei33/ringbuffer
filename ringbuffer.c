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
#include "ringbuffer.h"
#include "stdlib.h"



#define __API_MALLCO


#ifndef __API_MALLCO
uint8_t  ringbufferArray_A[RINGBUFFER_SIZE][SINGLE_BUFFER];    /* 缓冲数组 */
uint32_t ringbufferid_A[RINGBUFFER_SIZE];

uint8_t ringbufferArray_B[RINGBUFFER_SIZE][SINGLE_BUFFER];    /* 缓冲数组 */
uint32_t ringbufferid_B[RINGBUFFER_SIZE];
#endif

 /*
*********************************************************************************************************
*	函 数 名: ringbuffer_next
*	功能说明: 计算存储元素位置
*	形    参：addr 地址
*	返 回 值: 存储地址
*********************************************************************************************************
*/
uint8_t ringbuffer_next(uint8_t addr)
{
    return (addr >= RINGBUFFER_SIZE) ? 0 : addr;
}


 /*
*********************************************************************************************************
*	函 数 名: ringbuffer_length
*	功能说明: 计算余下空间长度
*	形    参：rb 句柄
*	返 回 值: 长度
*********************************************************************************************************
*/
uint8_t ringbuffer_length(ringbuffer *rb)
{
    uint8_t len = 0;
	uint8_t les = 0;
	les = rb->start - rb->end;
    /* 初始化情况 */
    if(rb->start <= rb->end)
    {
        len = rb->size - (les % rb->size);
        return len;
    }
    else
    {
        len = rb->size - (rb->start - rb->end);
        return len;
    }


}

 /*
*********************************************************************************************************
*	函 数 名: ringbuffer_isFull
*	功能说明: 缓冲区是否满
*	形    参：rb 句柄
*	返 回 值: 长度
*********************************************************************************************************
*/
uint8_t ringbuffer_isFull(ringbuffer *rb)
{
    uint8_t len = 0;
    len = ringbuffer_length(rb);    /* 剩余长度判断 */

    if(len <= 1)
    {
        return 0;
    }

    return 1;
}


 /*
*********************************************************************************************************
*	函 数 名: ringbuffer_isEmpty
*	功能说明: 缓冲区是否空
*	形    参：rb 句柄
*	返 回 值: 长度
*********************************************************************************************************
*/
uint8_t ringbuffer_isEmpty(ringbuffer *rb)
{
    uint8_t len = 0;
    len = ringbuffer_length(rb);    /* 剩余长度判断 */

    if(len >= 16)
    {
        return 0;
    }

    return 1;
}


 /*
*********************************************************************************************************
*	函 数 名: ringbuffer_Init
*	功能说明: ringbuffer初始化
*	形    参：*rb 句柄
*              size
*	返 回 值: 无
*********************************************************************************************************
*/
void ringbuffer_Init(ringbuffer *rb)
{
    /* 动态分配一个区域 */
    // uint8_t ringbufferArray[RINGBUFFER_SIZE][SINGLE_BUFFER];    /* 缓冲数组 */
    // uint32_t ringbufferid[RINGBUFFER_SIZE];

    //memset(ringbufferArray, 0, sizeof(ringbufferArray));

    rb->size = RINGBUFFER_SIZE;
    rb->start = 1;
    rb->end = 0;

    #ifdef __API_MALLCO

    rb->databuf = (uint8_t (*)[SINGLE_BUFFER])malloc(sizeof(uint8_t) * RINGBUFFER_SIZE * SINGLE_BUFFER);
    rb->idbuf = (uint32_t *)malloc(sizeof(uint32_t) * RINGBUFFER_SIZE);

    #else

    if(rb->Type == 1)
    {
        rb->databuf = ringbufferArray_A;
        rb->idbuf = ringbufferid_A;
    }

    if(rb->Type == 2)
    {
        rb->databuf = ringbufferArray_B;
        rb->idbuf = ringbufferid_B;
    }
    #endif



}


 /*
*********************************************************************************************************
*	函 数 名: ringbuffer_write
*	功能说明: ringbuffer写入数据
*	形    参：ringbuffer *rb , uint8_t *data
*	返 回 值: 无
*********************************************************************************************************
*/
void ringbuffer_write(ringbuffer *rb , uint8_t *data , uint32_t id, uint8_t slen)
{
    uint8_t i = 0;
    uint8_t pos = 0;

    if(ringbuffer_isFull(rb))
    {
		rb->isEmpty = 0;

		pos = ringbuffer_next(++rb->start);
		rb->start = pos;

#ifdef __DEBUG__
        rb->Txlen = ringbuffer_length(rb);
#endif
        (rb->idbuf)[pos] = id;

        for(i = 0; i < slen; i++)
        {
            (rb->databuf)[pos][i] = data[i];
        }

    }
	else
	{
		rb->isFull = 1;
	}

}


/*
*********************************************************************************************************
*	函 数 名: ringbuffer_read
*	功能说明: ringbuffer读取数据
*	形    参：ringbuffer *rb
*	返 回 值: 缓冲区数据
*********************************************************************************************************
*/
ringbuffer_cangroup ringbuffer_read(ringbuffer *rb)
{

    uint8_t pos = 0;
    ringbuffer_cangroup rbg;

    if(ringbuffer_isEmpty(rb))
    {
		rb->isFull = 0;

		pos = ringbuffer_next(++rb->end);
		rb->end = pos;

#ifdef __DEBUG__
        rb->Rxlen = ringbuffer_length(rb);
#endif
        rbg.id = &(rb->idbuf[pos]);

        rbg.data = &((rb->databuf)[pos][0]);



        return  rbg;
    }
    else
    {
		rb->isEmpty = 1;

        rbg.id = 0;
        rbg.data = 0;

        return rbg;
    }
}


/*************************** vccw(END OF FILE)**********************************************************/
