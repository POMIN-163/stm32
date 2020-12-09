#ifndef _ClASS_GPIO_H_
#define _ClASS_GPIO_H_
#include "stm32f4xx.h"

class Class_GPIO{
    public:
/*
 * Set a GPIO's state or some GPIO's states with "|"
 * eg:
     GPIO
    ,GPIO_Pin
    ,GPIO_Mode
    ,GPIO_Speed
    ,GPIO_OType
    ,GPIO_PuPd
 */
    void Setting(
        GPIO_TypeDef* GPIOx,
        uint32_t GPIO_Pin,
        GPIOMode_TypeDef GPIO_Mode,
        GPIOSpeed_TypeDef GPIO_Speed,
        GPIOOType_TypeDef GPIO_OType,
        GPIOPuPd_TypeDef GPIO_PuPd
    );
/*
 * Set a GPIO's clock
 * eg:
    RCC_AHB1PeriphGPIO, DISABLE

    RCC_AHB1PeriphGPIO, ENABLE
 */
    void Clock(uint32_t RCC_AHB1Periph, FunctionalState NewState);
/*
 * Set a GPIO's state
 * eg:
    GPIO, GPIO_Pin, 1
    (HIGH)
    GPIO, GPIO_Pin, 0
    (LOW)
 */
    void SetBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState);
};


#endif
