#ifndef __SYS_H_
#define __SYS_H_
#include "stm32f4xx.h"

//***本部分代码参考与正点原子,不做商业用途***//

/*
 * Set a GPIO's state or some GPIO's states with "|"
 * eg:
    SysTick_CLKSource_HCLK, 168

    SysTick_CLKSource_HCLK_Div8, 168
 */
    void _SYS_Init(uint32_t SysTick_CLKSource_HCLK_, u8 SYSCLK);
/*
 * Set systick's time (us)
 */
    void _SYS_Delay_us(u32 us);
/*
 * Set systick's time (ms)
 */
    void _SYS_Delay_ms(u16 ms);

#endif
