#include "servo.h"

static uint32_t duty = 0;
static uint8_t dir = 0;

void servoInit(void) {
    gpioConf(GPIOB, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9, GPIO_Speed_10MHz, GPIO_Mode_AF_PP);

    timPwmConf(TIM4, 7200, 100, TIM_CounterMode_Up, TIM_CKD_DIV1,
           OC2, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_High);
    timPwmConf(TIM4, 7200, 100, TIM_CounterMode_Up, TIM_CKD_DIV1,
           OC3, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_High);
    timPwmConf(TIM4, 7200, 100, TIM_CounterMode_Up, TIM_CKD_DIV1,
           OC4, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_High);
    TIM_SetCompare2(TIM4, 0);
    TIM_SetCompare3(TIM4, 0);
    TIM_SetCompare4(TIM4, 0);
    TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);
    nvicIRQConf(TIM4_IRQn, 0x01, 0x03);
}
void TIM4_IRQHandler(void) {
    if(TIM_GetITStatus(TIM4, TIM_IT_CC2)|TIM_GetITStatus(TIM4, TIM_IT_CC3)|TIM_GetITStatus(TIM4, TIM_IT_CC4))
    {

    }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update | TIM_IT_CC4 |TIM_IT_CC2 | TIM_IT_CC3);  //清除中断标志位
}
