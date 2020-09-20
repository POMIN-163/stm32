#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
void (*gpio)();

int main(void){
	while(1){
		delay_init(168);
		gpio = led_Init;
		gpio();
		GPIO_SetBits(GPIOF,GPIO_Pin_9);
		GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		delay_ms(300);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		GPIO_SetBits(GPIOF,GPIO_Pin_10);
		delay_ms(300);
	}
}
