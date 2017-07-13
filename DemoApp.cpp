// DemoApp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "ringbuffer.h"



int _tmain(int argc, _TCHAR* argv[])
{
    ringbuffer rb;

    uint8_t Tx[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    uint8_t *p = 0;

    ringbuffer_Init(&rb);

    BYTE k = 0;

    for(int j = 0; j < 8; j++)
    {
        for(int i = 0; i < 8; i++)
        {
            Tx[i] = k++;     
        }

        ringbuffer_write(&rb,&Tx[0]);

        printf("写入第:%d次,余下空位置 %d,\n",j,rb.Txlen);
    }


    for(int i = 0; i <= 10; i++)
    {
        p = ringbuffer_read(&rb);

        if(p == 0) // 不要往0里面读数据导致出错
            break;

        for(int j = 0; j < 8; j++)
        {
            printf(" %d ",p[j]);
        }

        printf("\n");
        printf("读出第:%d次,余下空位置:%d,\n",i,rb.Rxlen);
        
    }

    
    system("pause");

	return 0;
}

