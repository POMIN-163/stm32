#include "usart.h"
// 此文件为串口中断
#if 1
	#pragma import(__use_no_semihosting)
	//标准库需要的支持函数
	struct __FILE {
		int handle;
	};
	FILE __stdout;
	//定义_sys_exit()以避免使用半主机模式
	void _sys_exit(int x) {
		x = x;
	}
	//重定义fputc函数
	int fputc(int ch, FILE *f) {
		while((USART1->SR & 0X40) == 0);//循环发送,直到发送完毕
		USART1->DR = (u8) ch;
		return ch;
	}
#endif

u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
// bit15，接收完成标志  bit14，接收到0x0d  bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记

void USART1_IRQHandler(void)// 串口1中断服务程序
{
    u8 Res;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据

        if((USART_RX_STA & 0x8000) == 0)//接收未完成
        {
            if(USART_RX_STA & 0x4000)//接收到了0x0d(\n)
            {
                if(Res != 0x0a) USART_RX_STA = 0;//接收错误,重新开始
                else USART_RX_STA |= 0x8000;	//接收完成了
            }
            else //还没收到0X0D
            {
                if(Res == 0x0d) USART_RX_STA |= 0x4000;
                else
                {
                    USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res ;
                    USART_RX_STA++;
                    if(USART_RX_STA>(USART_REC_LEN-1)) USART_RX_STA=0;//接收数据错误,重新开始接收
                }
            }
        }
    }
}
