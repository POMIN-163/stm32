#ifndef __KEY_H
#define __KEY_H

#include "system.h"

#define KEY0 GPIOB, GPIO_Pin_4
#define KEY1 GPIOB, GPIO_Pin_5

#define USE_MULTIBUTTON 1          // �Ƿ�ʹ�ð�����

#if 1 == USE_MULTIBUTTON
#include "multi_button.h"
#define allNum 2

extern void(*keyFun[allNum])(void);    // �������µ���Ӧ����
extern uint8_t keyFlag[allNum];        // ������Ӧ��־λ

void keyInit(void);
void keyScan(void);
void keyRun(void);

#endif
#endif
