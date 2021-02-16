#ifndef __LED_H
#define __LED_H
#include "global.h"

#define LED_PORT GPIOF
#define LED_PIN GPIO_PIN_10
#define LED_IO GPIOF,GPIO_PIN_10

void ledInit(void);

void ledOn(void);
void ledOff(void);
void ledToggle(void);

#endif
