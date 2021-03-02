#ifndef __LED_H
#define __LED_H
#include "system.h"

#define LED PCout(13)

void ledInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);

#endif
