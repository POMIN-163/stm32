#include "stm32f4xx.h"
#include "delay.h"
#include "tim.h"

int main ()
{
    GPIO_InitTypeDef gpio;
    _SYS_Init(SysTick_CLKSource_HCLK_Div8, 168);
		TIM2_Init(5000, 8400);
//led
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOF, &gpio);
    GPIO_SetBits(GPIOF, GPIO_Pin_10|GPIO_Pin_9);
    while(1){
       GPIO_SetBits(GPIOF, GPIO_Pin_10);
       _SYS_Delay_ms(500);
       GPIO_ResetBits(GPIOF, GPIO_Pin_10);
       _SYS_Delay_ms(500);
    }
 
}
