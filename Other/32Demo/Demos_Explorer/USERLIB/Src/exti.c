#include "exti.h"

void extiConf(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex,
  uint32_t EXTI_Line, EXTIMode_TypeDef EXTI_Mode, EXTITrigger_TypeDef EXTI_Trigger
) {
    EXTI_InitTypeDef EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOx, EXTI_PinSourcex);

    EXTI_InitStructure.EXTI_Line = EXTI_Line;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}
