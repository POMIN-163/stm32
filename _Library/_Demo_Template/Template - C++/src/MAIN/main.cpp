#include "Class_Sys.h"
#include "Class_GPIO.h"

Class_SYS sys;
Class_GPIO gpio;

void Init(void){
	sys.Init(SysTick_CLKSource_HCLK_Div8, 168);
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
		gpio.SetBit(GPIOF, GPIO_Pin_9|GPIO_Pin_10, 0);
		sys.Delay_ms(500);
		gpio.SetBit(GPIOF, GPIO_Pin_9|GPIO_Pin_10, 1);
		sys.Delay_ms(500);
	}
}

