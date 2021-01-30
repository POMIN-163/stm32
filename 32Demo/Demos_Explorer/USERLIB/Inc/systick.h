#ifndef __SYSTICK_H
#define __SYSTICK_H
#include "stm32f4xx.h"

void sysConf(uint32_t freq, uint8_t isDiv);
void sysDelayUS(uint32_t us);
void sysDelayMS(uint32_t ms);

#endif


