#ifndef __RNG_H
#define __RNG_H
#include "stm32f4xx.h"

uint8_t rngConf(void);
uint32_t rngGetRand(uint32_t min, uint32_t max);

#endif
