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
	u16 times=0;
	u8 flag = 0;
	Init();

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);// 取消写保护
	IWDG_SetPrescaler(8);// 设置IWDG分频系数
	IWDG_SetReload(500);// 重装载值
	IWDG_Enable();// 使能独立看门狗
	//时间计算(大概):Tout=((4*2^prer)*rlr)/32 (ms).

	while(1) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF);
		GPIO_SetBits(GPIOF, GPIO_Pin_9);

		if(flag == 0){
			printf("Begin working !!!\r\n");
			flag = 1;
		}
		if(USART_RX_STA&0x8000) {// 接收到信息导致死循环
			while(1);
		}else{
			times++;
			if(times % 200 == 0) printf("Working...\r\n");
			if(times % 30 == 0) LED1 = !LED1;//闪烁LED,提示系统正在运行.
			sys.Delay_ms(10);
		}
		IWDG_ReloadCounter();// 喂狗
	}
}

