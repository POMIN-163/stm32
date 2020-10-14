#include "beep.h"
#include "stm32f4xx.h"

void beep_Init(void){
    GPIO_InitTypeDef BEEP_init;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    BEEP_init.GPIO_Pin = GPIO_Pin_8;
    BEEP_init.GPIO_Speed = GPIO_Speed_100MHz;
    BEEP_init.GPIO_Mode = GPIO_Mode_OUT;
    BEEP_init.GPIO_OType = GPIO_OType_PP;
    BEEP_init.GPIO_PuPd = GPIO_PuPd_DOWN;// 默认0(蜂鸣器不响),所以下拉
    GPIO_Init(GPIOF, &BEEP_init);

}
