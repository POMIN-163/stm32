#include "nvic.h"

static int8_t isSetGroup = 0;

void nvicGroupConf(uint32_t NVIC_PriorityGroup) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
    isSetGroup = 1;
}
void nvicIRQConf(uint8_t NVIC_IRQCh, uint8_t NVIC_Rob_Rriority, uint8_t NVIC_Son_Priority) {
    NVIC_InitTypeDef NVIC_InitStruct;
    if(isSetGroup) {
        NVIC_InitStruct.NVIC_IRQChannel = NVIC_IRQCh;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = NVIC_Rob_Rriority;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = NVIC_Son_Priority;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
    }
}
