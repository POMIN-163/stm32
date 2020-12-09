#include "stm32f10x.h"
#include "system.h"
#include "delay.h"
#include "GPIO.h"
#include "TM1637.h"
/*
*按键：PA1、   2、    3
*     启动、 暂停、 清零
*数码管：PA8、 9
*       DIO、 CLK
*/
u8 G_status = 0;
// 1: 计数, 2: 暂停, 3: 清零
u8 G_time[2] = {0, 0,};
// 秒、10ms
u8 time[4] = {0x3f, 0x3f, 0x3f, 0x4f,};

unsigned const char LED_0_9[10]={
    // 0:	1	 2:	  3	  4:	5   6:	 7	 8:	  9
    0xbf,0x06,0xdb,0x4f,0xe6,0x6d,0xfd,0x07,0xff,0x6f};

void TIM3_Init(u16 arr,u16 psc);// 计时器
void TIM2_Init(u16 arr,u16 psc);// 刷新率
void Init(void);
void Transfrom(void);
u8 Keyscan(void);

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
// 按键
    _GPIO_Config(
        GPIOA,
        GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
        GPIO_Mode_IPU, GPIO_Speed_50MHz
    );
// 数码管
    _GPIO_Config(
        GPIOA,
        GPIO_Pin_8 | GPIO_Pin_9,
        GPIO_Mode_Out_PP, GPIO_Speed_50MHz
    );
    delay_init();
    TIM2_Init(10, 720);// 100us
    TIM3_Init(100, 7200);// 10ms
    TM_Init();
}
u8 Keyscan(void){
    // 清零
    if(!PAin(3)){
        while(!PAin(3));
        return 3;
    // 暂停
    }if(!PAin(2)){
        while(!PAin(2));
        return 2;
    // 计数
    }if(!PAin(1)){
        while(!PAin(1));
        return 1;
    } return 0;
}

//定时器3中断, 计时器
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        // 计数
        switch(G_status){
        case 1:
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
            break;
        // 暂停
        case 2:
            break;
        // 清零
        case 3:
            G_time[0] = G_time[1] = 0;
            G_status = 0;
            break;
        }
    	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志
	}
}

// 定时器2中断, 数码管刷新
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        Transfrom();
        TM_Display(time);
    	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志
	}
}
// 二位(秒、10ms)转到四位字符
void Transfrom(void){
    time[3] = LED_0_9[G_time[0] % 10];
    time[2] = LED_0_9[G_time[0] / 10];
    time[1] = LED_0_9[G_time[1] % 10];
    time[0] = LED_0_9[G_time[1] / 10];
}
int main(void) {
    u8 temp;
    Init();// 各个管脚初始化
    while(1) {
        temp = Keyscan();
        if(G_status == 2 && temp == 2) G_status = temp = 1;// 暂停后启动计数
        if(temp) G_status = temp;
    }
}



