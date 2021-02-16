#ifndef __BEEP_H
#define __BEEP_H
#include "system.h"

#define BEEP PFout(8)

void beepInit(void);
void beepOn(void);
void beepOff(void);

#endif
