#include "Class_Sys.h"
#include "Class_GPIO.h"
#include "Class_USART.h"
#include "Led..Beep..Key.h"

Class_SYS sys;
Class_GPIO gpio;
Class_USART usart;

void Init(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	sys.Init(SysTick_CLKSource_HCLK_Div8, 168);// 系统延时
	gpio.Clock(RCC_AHB1Periph_GPIOA, ENABLE);// 端口使能
	usart.Clock(RCC_APB2Periph_USART1, ENABLE);// 串口使能
	usart.Config_AF(
		GPIOA
		,GPIO_Pin_9
		,GPIO_PinSource9
		,GPIO_Speed_50MHz
		,GPIO_OType_PP
		,GPIO_PuPd_UP
		,GPIO_AF_USART1
	);// 端口复用到串口(Rx)
	usart.Config_AF(
		GPIOA
		,GPIO_Pin_10
		,GPIO_PinSource10
		,GPIO_Speed_50MHz
		,GPIO_OType_PP
		,GPIO_PuPd_UP
		,GPIO_AF_USART1
	);// 端口复用到串口(Tx)
	usart.Config(
		USART1
		,115200
		,USART_WordLength_8b
		,USART_StopBits_1
		,USART_Parity_No
		,USART_HardwareFlowControl_None
		,USART_Mode_Rx | USART_Mode_Tx
	);// 配置串口
	usart.Cmd(USART1, ENABLE);// 使能串口
	usart.Config_IT(USART1, USART_IT_RXNE, ENABLE);// 设置模式
	usart.Config_NVIC(USART1_IRQn, 3, 3, ENABLE);// 设置中断
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
			len = USART_RX_STA & 0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			for(t = 0; t < len; t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         //向串口1发送数据
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA = 0;
		}else{
			times++;
			if(times % 200 == 0) printf("请输入数据,以回车键结束\r\n");
			if(times % 30 == 0) LED1 = !LED1;//闪烁LED,提示系统正在运行.
			sys.Delay_ms(10);
		}
	}
}

