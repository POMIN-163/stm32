#ifndef __XWDG_H
#define __XWDG_H
#include "stm32f4xx.h"

void IWDG_Init(u8 prer,u16 rlr);       // IWDG��ʼ��
void IWDG_Feed(void);                  // ι������

void WWDG_Init(u8 tr,u8 wr,u32 fprer); // ���ڿ��Ź���ʼ��

#endif
