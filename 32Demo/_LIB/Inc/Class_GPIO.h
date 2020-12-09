#ifndef _ClASS_GPIO_H_
#define _ClASS_GPIO_H_
#include "stm32f4xx.h"

class Class_GPIO{
   public:
/*
   gpio.Clock();// 使能时钟
   gpio.Config();// 配置端口
   gpio.SetBit();// 操作端口
 */
   void Tip(void);
/*
 * Set a GPIO's setting or some GPIOs' settings with "|"
 * eg:
     GPIO
    ,GPIO_Pin
    ,GPIO_Mode
    ,GPIO_Speed
    ,GPIO_OType
    ,GPIO_PuPd

   eg: GPIO, GPIO_Pin, GPIO_Mode, GPIO_Speed, GPIO_OType, GPIO_PuPd
 */
   void Config(
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
    RCC_AHB1Periph_GPIO, DISABLE

    RCC_AHB1Periph_GPIO, ENABLE
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

// 下为C语言函数
extern "C" {
   void _GPIO_Config(
      GPIO_TypeDef* GPIOx,
      uint32_t GPIO_Pin,
      GPIOMode_TypeDef GPIO_Mode,
      GPIOSpeed_TypeDef GPIO_Speed,
      GPIOOType_TypeDef GPIO_OType,
      GPIOPuPd_TypeDef GPIO_PuPd
   );
   void _GPIO_Clock(uint32_t RCC_AHB1Periph, FunctionalState NewState);
   void _GPIO_SetBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState);
}
#endif
