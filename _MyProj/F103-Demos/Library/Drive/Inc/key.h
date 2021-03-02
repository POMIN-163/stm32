#ifndef __KEY_H
#define __KEY_H

#include "system.h"

#define KEY0 GPIOB, GPIO_Pin_4
#define KEY1 GPIOB, GPIO_Pin_5

#define USE_MULTIBUTTON 1          // 是否使用按键库

#if 1 == USE_MULTIBUTTON
#include "multi_button.h"
#define allNum 2

extern void(*keyFun[allNum])(void);    // 按键按下的响应函数
extern uint8_t keyFlag[allNum];        // 按键响应标志位

void keyInit(void);
void keyScan(void);
void keyRun(void);

#endif
#endif
