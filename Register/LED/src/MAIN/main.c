#include "led.h"
#include "stm32f4xx.h"
#include "delay.h"

int main(void) {
    led_Init();
    delay_init(168);
    while (1)
    {
        #if 0
        // 方法：ODR 寄存器操作
            GPIOF -> ODR &= ~(1 << 9);// F9赋 0
            GPIOF -> ODR |= 1 << 10;// F10赋 1
            delay_ms (100);
            GPIOF -> ODR |= 1 << 9;// F9赋 1
            GPIOF -> ODR &= ~(1 << 10);// F10赋 0
            delay_ms (100);
        #elif 0
        // 方法：用 BSRR 寄存器操作
            GPIOF -> BSRRH = 1 << 9;
            GPIOF -> BSRRL = 1 << 10;
            delay_ms (100);
            GPIOF -> BSRRH = 1 << 10;
            GPIOF -> BSRRL = 1 << 9;
            delay_ms (100);
        #elif 0
        // 方法：位操作
            PFout(9) = 1;
            PFout(10) = 1;
            delay_ms (100);
            PFout(9) = 0;
            PFout(10) = 0;
            delay_ms (100);
        #else
        // 方法三的头文件定义以简化代码量
            led0 = 1;
            led1 = 0;
            delay_ms (100);
            led0 = 0;
            led1 = 1;
            delay_ms (100);
        #endif
    }
}
