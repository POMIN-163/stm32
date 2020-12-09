#include "led.h"
#include "stm32f4xx.h"
#include "delay.h"	
void led_Init(){
    GPIO_InitTypeDef LED_Init;// 结构体
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);// 时钟初始化
#if 0
    /*******同总线的F9、F10分开配置********/
    LED_Init.GPIO_Pin = GPIO_Pin_9;
    LED_Init.GPIO_Mode = GPIO_Mode_OUT;
    LED_Init.GPIO_OType = GPIO_OType_PP;
    LED_Init.GPIO_PuPd = GPIO_PuPd_UP;
    LED_Init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF,&LED_Init);// 初始化P9

    LED_Init.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOF,&LED_Init);// 初始化P10
#endif
#if 1
    /*******同总线的F9、F10共同配置********/

	LED_Init.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;// 9、10管脚"|"位或运算共同配置
    LED_Init.GPIO_Mode = GPIO_Mode_OUT;// 普通输出模式
    LED_Init.GPIO_OType = GPIO_OType_PP;// 推挽输出模式
    LED_Init.GPIO_Speed = GPIO_Speed_100MHz;// 100MHz
    LED_Init.GPIO_PuPd = GPIO_PuPd_UP;// 上拉
    GPIO_Init(GPIOF,&LED_Init);// 初始化
#endif
}

