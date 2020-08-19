#include "stm32f4xx.h"

void led_Init(){
    RCC -> AHB1ENR |= 1 << 5;//时钟使能

    // PF9
    GPIOF -> MODER &= ~(3 << 2 * 9);//(清零)
    GPIOF -> MODER |= 1 << 2 * 9;
    // PF9对应的18、19位赋值(0、1)
    GPIOF -> OSPEEDR &= ~(3 << 2 * 9);
    GPIOF -> OSPEEDR |= 2 << 2 * 9;
    // 输出速度
    GPIOF -> PUPDR &= ~(3 << 2 * 9);
    GPIOF -> PUPDR |= 1 << 2 * 9;
    // 上拉
    GPIOF -> OTYPER &= ~(1 << 9);
    GPIOF -> OTYPER |= 0 << 9;
    // 输出类型

    // PF10
    GPIOF -> MODER &= ~(3 << 2 * 10);
    GPIOF -> MODER |= 1 << 2 * 10;

    GPIOF -> OSPEEDR &= ~(3 << 2 * 10);
    GPIOF -> OSPEEDR |= 2 << 2 * 10;

    GPIOF -> PUPDR &= ~(3 << 2 * 10);
    GPIOF -> PUPDR |= 1 << 2 * 10;

    GPIOF -> OTYPER &= ~(1 << 10);
    GPIOF -> OTYPER |= 0 << 10;

}

