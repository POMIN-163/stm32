#ifndef _DELAY_H_
#define _DELAY_H_
#include "stm32f4xx.h"

void _SYS_Init(uint32_t SysTick_CLKSource_HCLK_, u8 SYSCLK);
void _SYS_Delay_us(u32 us);
void _SYS_Delay_xms(u16 ms);
void _SYS_Delay_ms(u16 ms);

#endif
