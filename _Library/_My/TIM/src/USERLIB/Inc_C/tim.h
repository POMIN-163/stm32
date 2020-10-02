#ifndef __TIM_H
#define __TIM_H
#include "sys.h"
#include "stm32f4xx.h"
#define LED1 PFout(9)
#define LED2 PFout(10)

void TIM2_Init(u16 arr,u16 psc);

#endif
