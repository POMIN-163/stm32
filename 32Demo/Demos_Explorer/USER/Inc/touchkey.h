#ifndef __TOUCH_H
#define __TOUCH_H
#include "pominLib.h"

#define KEY_TOUCH GPIOA, GPIO_Pin_5

extern uint8_t touchFlag;         // 触摸按键标志位
extern void (*touchkeyFun)(void); // 触摸按键响应函数

void touchInit(void);
void touchScan(void);
void touchRun(void);

#endif
