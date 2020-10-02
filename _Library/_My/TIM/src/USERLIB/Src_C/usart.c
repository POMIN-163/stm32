#include "usart.h"
// ���ļ�Ϊ�����ж�
#if 1
	#pragma import(__use_no_semihosting)
	//��׼����Ҫ��֧�ֺ���
	struct __FILE {
		int handle;
	};
	FILE __stdout;
	//����_sys_exit()�Ա���ʹ�ð�����ģʽ
	void _sys_exit(int x) {
		x = x;
	}
	//�ض���fputc����
	int fputc(int ch, FILE *f) {
		while((USART1->SR & 0X40) == 0);//ѭ������,ֱ���������
		USART1->DR = (u8) ch;
		return ch;
	}
#endif

u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
// bit15��������ɱ�־  bit14�����յ�0x0d  bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���

void USART1_IRQHandler(void)// ����1�жϷ������
{
    u8 Res;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res = USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������

        if((USART_RX_STA & 0x8000) == 0)//����δ���
        {
            if(USART_RX_STA & 0x4000)//���յ���0x0d(\n)
            {
                if(Res != 0x0a) USART_RX_STA = 0;//���մ���,���¿�ʼ
                else USART_RX_STA |= 0x8000;	//���������
            }
            else //��û�յ�0X0D
            {
                if(Res == 0x0d) USART_RX_STA |= 0x4000;
                else
                {
                    USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res ;
                    USART_RX_STA++;
                    if(USART_RX_STA>(USART_REC_LEN-1)) USART_RX_STA=0;//�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
}
