#ifndef __KEY_H
#define __KEY_H

#include "pominLib.h"

#define keyNum  3  // 普通按键个数
#define extiNum 0  // 按键中断个数
#define capNum  1  // 输入捕获按键个数
#define allNum  keyNum + extiNum + capNum

extern uint64_t captureValue;
extern uint32_t captureTime[2];

extern void(*keyFun[allNum])(void);    // 按键按下的响应函数
extern uint8_t keyFlag[allNum];        // 按键响应标志位

#define KEY_CAP keyNum + 0        // 捕获按键序号
#define KEY_EXTI0 keyNum + 0      // 中断按键序号

#define KEY0 GPIOE, GPIO_Pin_2
#define KEY1 GPIOE, GPIO_Pin_3
#define KEY2 GPIOE, GPIO_Pin_4
#define KEY_UP GPIOA, GPIO_Pin_0

void keyInit(void);
void keyScan(void);
void keyRun(void);

#endif
