#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
int main(void){
	while(1){
		delay_init(168);		  //初始化延时函数
		led_Init();

		GPIO_SetBits(GPIOF,GPIO_Pin_9);
		GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		delay_ms(300);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		GPIO_SetBits(GPIOF,GPIO_Pin_10);
		delay_ms(300);
	}
}
