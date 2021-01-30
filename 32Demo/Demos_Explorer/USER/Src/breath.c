#include "breath.h"

static uint32_t duty = 0;
static uint8_t dir = 0;

void breathLedInit(void) {
    gpioAFConf(GPIOF, GPIO_Pin_9, GPIO_High_Speed, GPIO_OType_PP, GPIO_PuPd_UP,
               Clock_APB1, RCC_APB1Periph_TIM14, GPIO_AF_TIM14);
    timPwmConf(TIM14, 840, 500, TIM_CounterMode_Up, TIM_CKD_DIV1,
           OC1, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_Low);
    TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
    nvicIRQConf(TIM8_TRG_COM_TIM14_IRQn, 0x01, 0x03);
}

void TIM8_TRG_COM_TIM14_IRQHandler(void) {
    if(TIM_GetITStatus(TIM14, TIM_IT_Update) == SET) {
        if(duty > 300) dir = 0;
        if(duty < 5) dir = 1;
        if(dir) duty++;
        else duty--;
        TIM_SetCompare1(TIM14,duty);	          // 修改比较值，修改占空比
    }
    TIM_ClearITPendingBit(TIM14, TIM_IT_Update);  //清除中断标志位
}
