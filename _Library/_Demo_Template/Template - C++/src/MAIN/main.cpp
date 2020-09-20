#include "Class_GPIO.h"
#include "stm32f4xx.h"
#include "delay.h"

int main(void){
    delay_init(168);
    Class_GPIO gpio;
    gpio.Clock(RCC_AHB1Periph_GPIOF, ENABLE);
    gpio.Setting(
        GPIOF
        ,GPIO_Pin_9|GPIO_Pin_10
        ,GPIO_Mode_OUT
        ,GPIO_Speed_100MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
    );
	while(1){
        gpio.SetBit(GPIOF, GPIO_Pin_9|GPIO_Pin_10, 1);
        delay_ms(300);
        gpio.SetBit(GPIOF, GPIO_Pin_9|GPIO_Pin_10, 0);
        delay_ms(300);
	}
}
