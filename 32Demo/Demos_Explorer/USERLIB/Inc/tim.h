#ifndef __TIM_H
#define __TIM_H
#include "stm32f4xx.h"

typedef enum {
    OC1,
    OC2,
    OC3,
    OC4,
} OC_TypeDef;

void timBaseConf(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                 uint16_t TIM_CounterMode, uint16_t TIM_CKD
);
void timPwmConf(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                uint16_t TIM_CounterMode, uint16_t TIM_CKD, OC_TypeDef OCx,
                uint16_t TIM_OCMode, uint16_t TIM_OutputState, uint16_t TIM_OCPolarity
);

#endif
