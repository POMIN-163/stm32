#include "main.h"

void Init(void){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    _SYS_Init(SysTick_CLKSource_HCLK_Div8, 72);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
// 灯
    _GPIO_Config(
        GPIOC,
        GPIO_Pin_13 ,
        GPIO_Mode_Out_PP, GPIO_Speed_50MHz
    );
// 蓝牙串口
    _GPIO_Config(
        GPIOA,
        GPIO_Pin_9 ,
        GPIO_Mode_Out_PP, GPIO_Speed_50MHz
    );
}
// 初始化
int main(void) {
    Init();
    PWM_Init(100, 7200);
    // 1/(72MHz/7200)s  10KHz 0.1ms
    TIM_SetCompare1(TIM4, 50);
    TIM_SetCompare2(TIM4, 50);
    TIM_SetCompare3(TIM4, 50);
    TIM_SetCompare4(TIM4, 50);
    // 占空比 50%
    while(1) {
        PCout(13) = !PCout(13);
			_SYS_Delay_ms(500);
    }
}

