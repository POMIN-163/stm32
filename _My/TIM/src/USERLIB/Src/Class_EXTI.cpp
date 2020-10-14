#include "Class_EXTI.h"

void Class_EXTI::Tip(void){
    while(1);
}

void Class_EXTI::Clock(uint32_t RCC_APB2Periph, FunctionalState NewState){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, NewState);
}

void Class_EXTI::Config_Line(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex){
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOx, EXTI_PinSourcex);
}

void Class_EXTI::Config_NVIC(
    uint8_t IRQChannel,
    uint8_t IRQChannelPreemptionPriority,
    uint8_t IRQChannelSubPriority,
    FunctionalState IRQChannelCmd
){
    NVIC_InitTypeDef Temp;
			Temp.NVIC_IRQChannel = IRQChannel;
			Temp.NVIC_IRQChannelPreemptionPriority = IRQChannelPreemptionPriority;
			Temp.NVIC_IRQChannelSubPriority = IRQChannelSubPriority;
			Temp.NVIC_IRQChannelCmd = IRQChannelCmd;
    NVIC_Init(&Temp);
}

void Class_EXTI::Config(
    uint32_t EXTI_Line,
    EXTIMode_TypeDef EXTI_Mode,
    EXTITrigger_TypeDef EXTI_Trigger,
    FunctionalState EXTI_LineCmd
){
    EXTI_InitTypeDef Temp;
			Temp.EXTI_Line = EXTI_Line;
			Temp.EXTI_LineCmd = EXTI_LineCmd;
			Temp.EXTI_Mode = EXTI_Mode;
			Temp.EXTI_Trigger = EXTI_Trigger;
	EXTI_Init(&Temp);
}
