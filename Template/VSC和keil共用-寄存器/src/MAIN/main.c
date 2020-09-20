#include "led.h"
#include "stm32f4xx.h"
#include "delay.h"

int main(void) {
    led_Init();
    delay_init(168);
    while (1)
    {
        #if 1
            //ODR赋值方法
            GPIOF -> ODR &= ~(1 << 9);// F9赋 0
            GPIOF -> ODR |= 1 << 10;// F10赋 1
            delay_ms (100);
            GPIOF -> ODR |= 1 << 9;// F9赋 1
            GPIOF -> ODR &= ~(1 << 10);// F10赋 0
            delay_ms (100);

        #endif
    }
}
