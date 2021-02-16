#ifndef __EXTI_H
#define __EXTI_H
#include "stm32f4xx.h"

void extiConf(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex,
  uint32_t EXTI_Line, EXTIMode_TypeDef EXTI_Mode, EXTITrigger_TypeDef EXTI_Trigger
);

#endif
