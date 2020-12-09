#ifndef __USART_H
#define __USART_H
// 加入本代码,支持printf函数,而不需要选择 use MicroLIB
// 原创：正点原子
#include "stdio.h"
#include "stm32f4xx.h"

//***本部分代码参考与正点原子,不做商业用途***//

#define USART_REC_LEN  			200  	//定义最大接收字节数 200

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART_RX_STA;         		//接收状态标记

#endif


