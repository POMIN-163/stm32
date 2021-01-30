#ifndef __XWDG_H
#define __XWDG_H
#include "stm32f4xx.h"

void IWDG_Init(u8 prer,u16 rlr);  // IWDG³õÊ¼»¯
void IWDG_Feed(void);             // Î¹¹·º¯Êý

void WWDG_Init(u8 tr,u8 wr,u32 fprer);

#endif
