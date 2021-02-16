#ifndef __XWDG_H
#define __XWDG_H
#include "stm32f4xx.h"

void IWDG_Init(u8 prer,u16 rlr);       // IWDG初始化
void IWDG_Feed(void);                  // 喂狗函数

void WWDG_Init(u8 tr,u8 wr,u32 fprer); // 窗口看门狗初始化

#endif
