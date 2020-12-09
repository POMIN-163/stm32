#ifndef __GPIO_H_
#define __GPIO_H_
#include "stm32f4xx.h"

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
    void _GPIO_Config(
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
    void _GPIO_Clock(uint32_t RCC_AHB1Periph, FunctionalState NewState);
/*
 * Set a GPIO's state
 * eg:
    GPIO, GPIO_Pin, 1
    (HIGH)
    GPIO, GPIO_Pin, 0
    (LOW)
 */
   void _GPIO_SetBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState);
/*
 * Set a GPIO's AF'setting or some GPIOs' AF'settings with "|"
 * eg:
     GPIO
    ,GPIO_Pin
    ,GPIO_PinSource
    ,GPIO_Speed
    ,GPIO_OType
    ,GPIO_PuPd
    ,GPIO_AF
 */
   void _GPIO_Config_AF(
      GPIO_TypeDef* GPIOx,
      uint32_t GPIO_Pin,
      uint16_t GPIO_PinSource,
      GPIOSpeed_TypeDef GPIO_Speed,
      GPIOOType_TypeDef GPIO_OType,
      GPIOPuPd_TypeDef GPIO_PuPd,
      uint8_t GPIO_AF
   );
#endif
