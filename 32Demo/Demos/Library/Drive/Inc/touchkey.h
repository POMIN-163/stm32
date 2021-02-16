#ifndef __TOUCH_H
#define __TOUCH_H
#include "system.h"

#define KEY_TOUCH GPIOA, GPIO_Pin_5

extern uint8_t touchFlag;                 // 触摸按键标志位
extern void (*touchkeyFun)(void);         // 触摸按键响应函数
extern volatile uint16_t touchDefult; // 触摸按键空载值

void touchInit(void);
void touchScan(void);
void touchRun(void);

#endif
