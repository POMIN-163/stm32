#ifndef __KEY_H
#define __KEY_H

#include "pominLib.h"

#define keyNum 3   // 普通按键个数
#define extiNum 1  // 按键中断个数

extern void(*keyFun[keyNum])(void);    // 普通按键按下的响应函数
extern void(*extiFun[extiNum])(void);  // 外部中断按键按下的响应函数

#define KEY0 GPIOE, GPIO_Pin_2
#define KEY1 GPIOE, GPIO_Pin_3
#define KEY2 GPIOE, GPIO_Pin_4
#define KEY_UP GPIOA, GPIO_Pin_0

void keyInit(void);
void keyScan(void);

#endif
