#include "tim.h"

//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
void TIM2_Init(u16 arr,u16 psc){
    TIM_TimeBaseInitTypeDef tim2;
    NVIC_InitTypeDef tim2NVIC;
    // TIM_TimeBaseInitTypeDef * tim2;
    // NVIC_InitTypeDef * tim2NVIC;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//1
        tim2.TIM_Period = arr - 1;//自动重装载值
		tim2.TIM_Prescaler = psc - 1;//定时器分频
        tim2.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
        tim2.TIM_ClockDivision = TIM_CKD_DIV1;// 分频
        TIM_TimeBaseInit(TIM2, &tim2);
//2
		// tim2->TIM_Period = arr - 1;
		// tim2->TIM_Prescaler = psc - 1;
        // tim2->TIM_CounterMode = TIM_CounterMode_Up;
        // tim2->TIM_ClockDivision = TIM_CKD_DIV1;
        // TIM_TimeBaseInit(TIM2, tim2);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
//1
	tim2NVIC.NVIC_IRQChannel = TIM2_IRQn; //定时器3中断
	tim2NVIC.NVIC_IRQChannelPreemptionPriority = 0x01; //抢占优先级1
	tim2NVIC.NVIC_IRQChannelSubPriority = 0x03; //子优先级3
	tim2NVIC.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&tim2NVIC);
//2
    // tim2NVIC->NVIC_IRQChannel = TIM2_IRQn;
	// tim2NVIC->NVIC_IRQChannelPreemptionPriority = 0x01;
	// tim2NVIC->NVIC_IRQChannelSubPriority = 0x03;
	// tim2NVIC->NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(tim2NVIC);
//
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}

