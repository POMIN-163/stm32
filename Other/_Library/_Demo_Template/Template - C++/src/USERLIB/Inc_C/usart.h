#ifndef __USART_H
#define __USART_H
// ���뱾����,֧��printf����,������Ҫѡ�� use MicroLIB
// ԭ��������ԭ��
#include "stdio.h"
#include "stm32f4xx.h"

//***�����ִ���ο�������ԭ��,������ҵ��;***//

#define USART_REC_LEN  			200  	//�����������ֽ��� 200

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART_RX_STA;         		//����״̬���

#endif


