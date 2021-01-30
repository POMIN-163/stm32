#ifndef __LED_H
#define __LED_H
#include "pominLib.h"

#define LED0 GPIOF, GPIO_Pin_9
#define LED1 GPIOF, GPIO_Pin_10

void ledInit(void);
void ledOn(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void ledOff(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void ledToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);


#endif
