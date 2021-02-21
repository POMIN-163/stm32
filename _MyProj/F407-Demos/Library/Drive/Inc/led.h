#ifndef __LED_H
#define __LED_H
#include "system.h"

#define LED PFout(10)

void ledInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);

#endif
