#ifndef __KEY_H
#define __KEY_H

#include "pominLib.h"

#define keyNum  3  // ��ͨ��������
#define extiNum 0  // �����жϸ���
#define capNum  1  // ���벶�񰴼�����
#define allNum  keyNum + extiNum + capNum

extern uint64_t captureValue;
extern uint32_t captureTime[2];

extern void(*keyFun[allNum])(void);    // �������µ���Ӧ����
extern uint8_t keyFlag[allNum];        // ������Ӧ��־λ

#define KEY_CAP keyNum + 0        // ���񰴼����
#define KEY_EXTI0 keyNum + 0      // �жϰ������

#define KEY0 GPIOE, GPIO_Pin_2
#define KEY1 GPIOE, GPIO_Pin_3
#define KEY2 GPIOE, GPIO_Pin_4
#define KEY_UP GPIOA, GPIO_Pin_0

void keyInit(void);
void keyScan(void);
void keyRun(void);

#endif
