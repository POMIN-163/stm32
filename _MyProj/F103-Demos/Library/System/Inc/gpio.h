#ifndef __GPIO_H
#define __GPIO_H
#include "stm32f10x.h"

void gpioConf(
    GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed,
    GPIOMode_TypeDef GPIO_Mode
);
/*
void gpioAFConf(
    GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd, uint8_t GPIO_AF
);
*/
void gpioInputSet(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState);
void gpioOutputSet(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState);
uint8_t gpioInputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
uint8_t gpioOutputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void gpioInputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void gpioOutputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

#endif
