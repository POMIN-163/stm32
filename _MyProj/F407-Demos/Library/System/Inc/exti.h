#ifndef __EXTI_H
#define __EXTI_H
#include "stm32f4xx.h"

void extiConf(uint32_t EXTI_Line, EXTIMode_TypeDef EXTI_Mode,
              EXTITrigger_TypeDef EXTI_Trigger);

void extiGpioConf(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin,
                  uint32_t EXTI_Line, EXTIMode_TypeDef EXTI_Mode,
                  EXTITrigger_TypeDef EXTI_Trigger
);

#endif
