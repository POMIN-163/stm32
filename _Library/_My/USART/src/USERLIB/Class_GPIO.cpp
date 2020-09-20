#include "Class_GPIO.h"
#include "stm32f4xx.h"

void Class_GPIO::Setting(
    GPIO_TypeDef* GPIOx,
    uint32_t GPIO_Pin,
    GPIOMode_TypeDef GPIO_Mode,
    GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType,
    GPIOPuPd_TypeDef GPIO_PuPd
){
    GPIO_InitTypeDef Temp={GPIO_Pin, GPIO_Mode, GPIO_Speed, GPIO_OType, GPIO_PuPd};
    GPIO_Init(GPIOx, &Temp);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
}
void Class_GPIO::Clock(uint32_t RCC_AHB1Periph, FunctionalState NewState) {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph,NewState);
}
void Class_GPIO::SetBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState){
    if(NewState)
        GPIO_SetBits(GPIOx,GPIO_Pin);
    else
        GPIO_ResetBits(GPIOx,GPIO_Pin);
}
