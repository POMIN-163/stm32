#include "Class_Sys.hpp"
#include "Class_GPIO.hpp"

Class_SYS sys;
Class_GPIO gpio;

void Init(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	sys.Init(SysTick_CLKSource_HCLK_Div8, 168);// 系统延时
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
	Init();
	while(1) {
		_SYS_Delay_ms(500);
		GPIO_SetBits(GPIOF, GPIO_Pin_9|GPIO_Pin_10);
		_SYS_Delay_ms(500);
		GPIO_ResetBits(GPIOF, GPIO_Pin_9|GPIO_Pin_10);
	}
}

