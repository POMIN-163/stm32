#include "Class_Sys.h"
#include "Class_GPIO.h"
#include "Class_USART.h"
#include "Led..Beep..Key.h"

Class_SYS sys;
Class_GPIO gpio;
Class_USART usart;

void Init(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	sys.Init(SysTick_CLKSource_HCLK_Div8, 168);// ϵͳ��ʱ
	gpio.Clock(RCC_AHB1Periph_GPIOA, ENABLE);// �˿�ʹ��
	usart.Clock(RCC_APB2Periph_USART1, ENABLE);// ����ʹ��
	usart.Config_AF(
		GPIOA
		,GPIO_Pin_9
		,GPIO_PinSource9
		,GPIO_Speed_50MHz
		,GPIO_OType_PP
		,GPIO_PuPd_UP
		,GPIO_AF_USART1
	);// �˿ڸ��õ�����(Rx)
	usart.Config_AF(
		GPIOA
		,GPIO_Pin_10
		,GPIO_PinSource10
		,GPIO_Speed_50MHz
		,GPIO_OType_PP
		,GPIO_PuPd_UP
		,GPIO_AF_USART1
	);// �˿ڸ��õ�����(Tx)
	usart.Config(
		USART1
		,115200
		,USART_WordLength_8b
		,USART_StopBits_1
		,USART_Parity_No
		,USART_HardwareFlowControl_None
		,USART_Mode_Rx | USART_Mode_Tx
	);// ���ô���
	usart.Cmd(USART1, ENABLE);// ʹ�ܴ���
	usart.Config_IT(USART1, USART_IT_RXNE, ENABLE);// ����ģʽ
	usart.Config_NVIC(USART1_IRQn, 3, 3, ENABLE);// �����ж�
	gpio.Clock(RCC_AHB1Periph_GPIOF, ENABLE);// LED
	gpio.Config(
		 GPIOF
		,GPIO_Pin_9|GPIO_Pin_10
		,GPIO_Mode_OUT
		,GPIO_Speed_50MHz
		,GPIO_OType_PP
		,GPIO_PuPd_UP
	);
}

int main(void) {
	u8 t;
	u8 len;
	u16 times=0;
	Init();
	while(1) {
		if(USART_RX_STA&0x8000) {
			len = USART_RX_STA & 0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t = 0; t < len; t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA = 0;
		}else{
			times++;
			if(times % 200 == 0) printf("����������,�Իس�������\r\n");
			if(times % 30 == 0) LED1 = !LED1;//��˸LED,��ʾϵͳ��������.
			sys.Delay_ms(10);
		}
	}
}

