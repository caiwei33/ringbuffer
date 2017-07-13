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
#include "string.h"


uint8_t ringbufferArray[RINGBUFFER_SIZE][SINGLE_BUFFER];    /* 缓冲数组 */

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
    return (addr == RINGBUFFER_SIZE) ? 0 : addr ;
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
    /* 初始化情况 */
    if(rb->start < rb->end)
    {
        return rb->size - ((rb->start - rb->end) % rb->size);
    }
    else
    {
        return rb->size - (rb->start - rb->end);
    }
    
    
}


 /*
*********************************************************************************************************
*	函 数 名: ringbuffer_Init
*	功能说明: ringbuffer初始化
*	形    参：*rb 句柄 
              size 
*	返 回 值: 无
*********************************************************************************************************
*/
void ringbuffer_Init(ringbuffer *rb)
{
    memset(ringbufferArray, 0, sizeof(ringbufferArray));

    rb->size = RINGBUFFER_SIZE;
    rb->start = 1;
    rb->end = 0;
    rb->buf = &ringbufferArray[0][0];
}
 
 
 /*
*********************************************************************************************************
*	函 数 名: ringbuffer_write
*	功能说明: ringbuffer写入数据
*	形    参：ringbuffer *rb , uint8_t *data
*	返 回 值: 无
*********************************************************************************************************
*/
void ringbuffer_write(ringbuffer *rb , uint8_t *data)
{
    uint8_t len = 0;
    uint8_t i = 0;
    uint8_t pos = 0;
    
    len = ringbuffer_length(rb);    /* 剩余长度判断 */
    pos = ringbuffer_next(rb->start);
    rb->start++;
    
    if(len > 1)
    {
#ifdef __DEBUG__

        rb->Txlen = len; 
#endif
        for(i = 0; i < 8; i++)
        {
            ringbufferArray[pos][i] = data[i];
        }
    }
    else
    {
        
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
uint8_t *ringbuffer_read(ringbuffer *rb)
{
    uint8_t len = 0;
    uint8_t i = 0;
    uint8_t pos = 0;
    
    len = ringbuffer_length(rb);    /* 剩余长度判断 */
    pos = ringbuffer_next(rb->end);
    rb->end++;

    if(len <= RINGBUFFER_SIZE - 1)
    {

#ifdef __DEBUG__
        rb->Rxlen = len; 
#endif
           return  &ringbufferArray[pos][0];
    }
    else
    {
        return 0;
    }
}
 
 
/*************************** vccw(END OF FILE)**********************************************************/