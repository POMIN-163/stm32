#include "breath.h"

static uint32_t duty = 0;
static uint8_t dir = 0;

void breathLedInit(void) {
    gpioConf(GPIOA, GPIO_Pin_6 | GPIO_Pin_7, GPIO_Speed_10MHz, GPIO_Mode_AF_PP);
    gpioConf(GPIOB, GPIO_Pin_0, GPIO_Speed_10MHz, GPIO_Mode_AF_PP);

    timPwmConf(TIM3, 720, 500, TIM_CounterMode_Up, TIM_CKD_DIV1,
           OC1, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_High);
    timPwmConf(TIM3, 720, 500, TIM_CounterMode_Up, TIM_CKD_DIV1,
           OC2, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_High);
    timPwmConf(TIM3, 720, 500, TIM_CounterMode_Up, TIM_CKD_DIV1,
           OC3, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_High);
    TIM_SetCompare1(TIM3, 0);
    TIM_SetCompare2(TIM3, 0);
    TIM_SetCompare3(TIM3, 0);
    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);
    nvicIRQConf(TIM3_IRQn, 0x01, 0x03);
}
uint8_t ledRgb = 0;
void TIM3_IRQHandler(void) {
    switch (ledRgb)
    {
    case 0:
        if(duty > 300) dir = 0;
        if(duty < 2) {
            ledRgb++;
            dir = 1;
        }
        if(dir) duty++;
        else duty--;
        TIM_SetCompare1(TIM3,duty);
        break;
    case 1:
        if(duty > 300) dir = 0;
        if(duty < 2) {
            ledRgb++;
            dir = 1;
        }
        if(dir) duty++;
        else duty--;
        TIM_SetCompare2(TIM3,duty);
        break;
    case 2:
        if(duty > 300) dir = 0;
        if(duty < 2) {
            ledRgb++;
            dir = 1;
        }
        if(dir) duty++;
        else duty--;
        TIM_SetCompare3(TIM3,duty);
        break;
    default:
        ledRgb = 0;
        break;
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update | TIM_IT_CC1 |TIM_IT_CC2 | TIM_IT_CC3);  //清除中断标志位
}
