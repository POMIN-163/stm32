#ifndef _ClASS_EXTI_H_
#define _ClASS_EXTI_H_
#include "exti.h"

//***本部分代码参考与正点原子,不做商业用途***//

class Class_EXTI{
    public:
/*
   exti.Clock();// 使能时钟
   exti.Config_Line();// 中断线配置
   exti.Config();// 中断配置
   exti.Config_NVIC();// 优先级配置
 */
   void Tip(void);
/*
 * Set a EXTI's line
 * eg:
      EXTI_PortSourceGPIO, EXTI_PinSource
 */
   void Config_Line(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
/*
 * Set a EXTI's state
 * eg:
      EXTI_Line,
      EXTI_Mode,
      EXTI_Trigger,
      ENABLE
 */
   void Config(
      uint32_t EXTI_Line,
      EXTIMode_TypeDef EXTI_Mode,
      EXTITrigger_TypeDef EXTI_Trigger,
      FunctionalState EXTI_LineCmd
   );
/*
 * Set EXTI's Clock
 * eg:
     RCC_APB2Periph_SYSCFG, ENABLE
 */
   void Clock(uint32_t RCC_APB2Periph, FunctionalState NewState);
/*
 * Set EXTI's NVIC
 * eg:
     EXTI0_IRQn, 0, 2, ENABLE
 */
   void Config_NVIC(
      uint8_t NVIC_IRQChannel,
      uint8_t NVIC_IRQChannelPreemptionPriority,
      uint8_t NVIC_IRQChannelSubPriority,
      FunctionalState NVIC_IRQChannelCmd
   );
};

#endif
