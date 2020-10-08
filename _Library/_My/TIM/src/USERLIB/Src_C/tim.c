#include "tim.h"

//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
void TIM2_Init(u16 arr,u16 psc){
    TIM_TimeBaseInitTypeDef tim2;
    NVIC_InitTypeDef tim2NVIC;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
        tim2.TIM_Period = arr - 1;//自动重装载值
		tim2.TIM_Prescaler = psc - 1;//定时器分频
        tim2.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
        tim2.TIM_ClockDivision = TIM_CKD_DIV1;// 分频
        TIM_TimeBaseInit(TIM2, &tim2);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	tim2NVIC.NVIC_IRQChannel = TIM2_IRQn; //定时器3中断
	tim2NVIC.NVIC_IRQChannelPreemptionPriority = 0x01; //抢占优先级1
	tim2NVIC.NVIC_IRQChannelSubPriority = 0x03; //子优先级3
	tim2NVIC.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&tim2NVIC);
}


//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
void TIM14_Init(u16 arr,u16 psc){
    TIM_TimeBaseInitTypeDef tim14;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);// 使能时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

		GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14); // 复用定时器
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOF,&GPIO_InitStructure);              //初始化PF9

        tim14.TIM_Period = arr - 1;//自动重装载值
				tim14.TIM_Prescaler = psc - 1;//定时器分频
        tim14.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
        tim14.TIM_ClockDivision = TIM_CKD_DIV1;// 分频
    TIM_TimeBaseInit(TIM14, &tim14);


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);
 TIM_ARRPreloadConfig(TIM14,ENABLE);
	TIM_Cmd(TIM14,ENABLE);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET) //溢出中断
	{
		LED2=!LED2;
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}

