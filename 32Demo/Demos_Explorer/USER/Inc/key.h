#ifndef __KEY_H
#define __KEY_H

#include "pominLib.h"

#define keyNum 3   // ��ͨ��������
#define extiNum 1  // �����жϸ���

extern void(*keyFun[keyNum])(void);    // ��ͨ�������µ���Ӧ����
extern void(*extiFun[extiNum])(void);  // �ⲿ�жϰ������µ���Ӧ����

#define KEY0 GPIOE, GPIO_Pin_2
#define KEY1 GPIOE, GPIO_Pin_3
#define KEY2 GPIOE, GPIO_Pin_4
#define KEY_UP GPIOA, GPIO_Pin_0

void keyInit(void);
void keyScan(void);

#endif
