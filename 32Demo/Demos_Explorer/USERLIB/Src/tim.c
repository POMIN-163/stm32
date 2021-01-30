#include "tim.h"


void timBaseConf(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                 uint16_t TIM_CounterMode, uint16_t TIM_CKD
) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    switch ((uint32_t)TIMx)
    {
    case TIM1_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
        break;
    case TIM2_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
        break;
    case TIM3_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
        break;
    case TIM4_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
        break;
    case TIM5_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
        break;
    case TIM6_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
        break;
    case TIM7_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
        break;
    case TIM8_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
        break;
    case TIM9_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
        break;
    case TIM10_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
        break;
    case TIM11_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
        break;
    case TIM12_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
        break;
    case TIM13_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
        break;
    case TIM14_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
        break;
    default:
        break;
    }
    // 配置基本定时器
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD;
    TIM_TimeBaseInitStruct.TIM_Period = TIM_Period - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM_Prescaler - 1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);
    TIM_ITConfig(TIMx,TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}
void timPwmConf(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                uint16_t TIM_CounterMode, uint16_t TIM_CKD, OC_TypeDef OCx,
                uint16_t TIM_OCMode, uint16_t TIM_OutputState, uint16_t TIM_OCPolarity
) {
    TIM_OCInitTypeDef TIM_OCInitStruct;
    // 配置基本定时器
    timBaseConf(TIMx,TIM_Prescaler,TIM_Period,TIM_CounterMode,TIM_CKD);
    // 配置 PWM 波输出通道
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity;
    switch (OCx)
    {
    case OC1: TIM_OC1Init(TIMx, &TIM_OCInitStruct); TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable); break;
    case OC2: TIM_OC2Init(TIMx, &TIM_OCInitStruct); TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable); break;
    case OC3: TIM_OC3Init(TIMx, &TIM_OCInitStruct); TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable); break;
    case OC4: TIM_OC4Init(TIMx, &TIM_OCInitStruct); TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable); break;
    default:
        break;
    }
    TIM_ARRPreloadConfig(TIMx,ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}

TIM_ICInitTypeDef  TIM5_ICInitStructure;

//定时器5通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0复用位定时器5


	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);


	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断

  TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5


  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、


}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
//定时器5中断服务程序
void TIM5_IRQHandler(void)
{

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//溢出
		{
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
			{
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			  TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//获取当前的捕获值.
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_Cmd(TIM5,DISABLE ); 	//关闭定时器5
	 			TIM_SetCounter(TIM5,0);
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
				TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
			}
		}
 	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}



