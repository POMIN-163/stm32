#ifndef __BEEP_H
#define __BEEP_H
#include "global.h"

#define BEEP_PORT GPIOF
#define BEEP_PIN GPIO_PIN_8
#define BEEP_IO GPIOF,GPIO_PIN_8

void beepInit(void);
void beepOn(void);
void beepOff(void);

#endif
