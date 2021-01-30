#ifndef __BEEP_H
#define __BEEP_H
#include "pominLib.h"

#define BEEP GPIOF, GPIO_Pin_8

void beepInit(void);
void beepOn(void);
void beepOff(void);

#endif
