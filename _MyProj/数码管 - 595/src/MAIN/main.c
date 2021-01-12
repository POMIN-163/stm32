#include "stm32f10x.h"
#include "system.h"
#include "SYS.h"
#include "GPIO.h"

#define SCLK PAout(1)
#define RCLK PAout(2)
#define DIO PAout(3)

u8 G_time[2] = {0, 0,};

unsigned const char LED_0_F[17] =
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};

void TIM3_Init(u16 arr,u16 psc);// 计时
void TIM2_Init(u16 arr,u16 psc);// 刷新
void LED_OUT(u8 X) ;
void Display (void);
void Init(void);

void TIM3_Init(u16 arr,u16 psc) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx
}
void TIM2_Init(u16 arr,u16 psc) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);
}
void Init(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
// 灯
    _GPIO_Config(
        GPIOC,
        GPIO_Pin_13,
        GPIO_Mode_Out_PP, GPIO_Speed_50MHz
    );
    _GPIO_Config(
        GPIOA,
        GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
        GPIO_Mode_Out_PP, GPIO_Speed_50MHz
    );
    _SYS_Init(SysTick_CLKSource_HCLK_Div8, 72);
    TIM2_Init(10, 72);// 100us
    TIM3_Init(10000, 7200);// 1s
}

void Display (void) {
	LED_OUT(LED_0_F[G_time[0] % 10]);
	LED_OUT(0x01);
	RCLK = 0; RCLK = 1;

	LED_OUT(LED_0_F[G_time[0] / 10]);
	LED_OUT(0x02);
	RCLK = 0; RCLK = 1;

	LED_OUT(LED_0_F[G_time[1] % 10]);
	LED_OUT(0x04);
	RCLK = 0; RCLK = 1;

	LED_OUT(LED_0_F[G_time[1] / 10]);
	LED_OUT(0x08);
	RCLK = 0; RCLK = 1;

}
void LED_OUT(u8 X) {
	u8 i;
	for(i = 8; i >= 1; i--) {
		if (X & 0x80)
            DIO = 1;
        else
            DIO = 0;
		X <<= 1;
		SCLK = 0;
		SCLK = 1;
	}
}

//定时器3中断, 计时器
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        if(G_time[0] == 99 && G_time[1] == 99){
        }
        else {
            G_time[0]++;
            if(G_time[0] == 100) {
                G_time[0] = 0;
                G_time[1]++;
                PCout(13) = ! PCout(13);
            }
        }
    	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志
	}
}
// 定时器2中断, 数码管刷新
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
       // Display();
    	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志
	}
}
int main(void) {
    Init();// 各个管脚初始化
    while(1) {
		LED_OUT(LED_0_F[0]);
		LED_OUT(0xf0);
		RCLK = 0; RCLK = 1;
    }
}


