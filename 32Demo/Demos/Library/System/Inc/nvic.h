#ifndef __NVIC_H
#define __NVIC_H
#include "stm32f4xx.h"

void nvicGroupConf(uint32_t NVIC_PriorityGroup);
void nvicIRQConf(uint8_t NVIC_IRQCh, uint8_t NVIC_Rob_Rriority, uint8_t NVIC_Son_Priority);

#endif
