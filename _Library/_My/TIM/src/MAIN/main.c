#include "stm32f4xx.h"
#include "delay.h"
#include "tim.h"

int main ()
{
    GPIO_InitTypeDef gpio;
    u16 led0pwmval=0;
	u8 dir=1;
    _SYS_Init(SysTick_CLKSource_HCLK_Div8, 168);
		TIM2_Init(5000, 8400);

//led
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOF, &gpio);
    GPIO_SetBits(GPIOF, GPIO_Pin_10);
    TIM14_Init(500, 84);
    TIM14_Init(500, 84);
    while(1){
    /*   GPIO_SetBits(GPIOF, GPIO_Pin_10);
       _SYS_Delay_ms(500);
       GPIO_ResetBits(GPIOF, GPIO_Pin_10);*/
       _SYS_Delay_ms(10);
		if(dir)led0pwmval++;//dir==1 led0pwmval递增
		else led0pwmval--;	//dir==0 led0pwmval递减
 		if(led0pwmval>300)dir=0;//led0pwmval到达300后，方向为递减
		if(led0pwmval==0)dir=1;	//led0pwmval递减到0后，方向改为递增
		TIM_SetCompare1(TIM14,led0pwmval);	//修改比较值，修改占空比
    }
}

