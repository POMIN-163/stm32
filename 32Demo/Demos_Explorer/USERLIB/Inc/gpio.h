#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f4xx.h"

typedef enum
{
    Clock_AHB1 = 0x01,
    Clock_AHB2 = 0x02,
    Clock_AHB3 = 0x03,
    Clock_APB1 = 0x04,
    Clock_APB2 = 0x05
} Clock_TypeDef;

void gpioConf(
    GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed,
    GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd
);
void gpioAFConf(
    GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd,
    Clock_TypeDef Clock_AxBx, uint32_t RCC_AxBxPeriph, uint8_t GPIO_AF
);

void gpioInputSet(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState);
void gpioOutputSet(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState);
uint8_t gpioInputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
uint8_t gpioOutputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void gpioInputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void gpioOutputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

#endif
