#ifndef __HC_SR04_H
#define __HC_SR04_H
#include "system.h"

#define TRIG GPIOB, GPIO_Pin_5
#define ECHO GPIOB, GPIO_Pin_6

#define HC_TIM TIM9
#define HC_IRQ TIM1_BRK_TIM9_IRQn

void hcsr04Init(void);
uint32_t hcsr04GetLength(void);

#endif
