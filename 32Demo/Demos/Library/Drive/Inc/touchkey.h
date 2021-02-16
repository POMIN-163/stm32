#ifndef __TOUCH_H
#define __TOUCH_H
#include "system.h"

#define KEY_TOUCH GPIOA, GPIO_Pin_5

extern uint8_t touchFlag;                 // ����������־λ
extern void (*touchkeyFun)(void);         // ����������Ӧ����
extern volatile uint16_t touchDefult; // ������������ֵ

void touchInit(void);
void touchScan(void);
void touchRun(void);

#endif
