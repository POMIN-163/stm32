#include "Class_GPIO.h"

void Class_GPIO::Config(
    GPIO_TypeDef* GPIOx,
    uint32_t GPIO_Pin,
    GPIOMode_TypeDef GPIO_Mode,
    GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType,
    GPIOPuPd_TypeDef GPIO_PuPd
) {
    GPIO_InitTypeDef Temp={GPIO_Pin, GPIO_Mode, GPIO_Speed, GPIO_OType, GPIO_PuPd};
    GPIO_Init(GPIOx, &Temp);
}

void Class_GPIO::Clock(uint32_t RCC_AHB1Periph, FunctionalState NewState) {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph,NewState);
}

void Class_GPIO::SetBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState) {
    if(NewState)
        GPIO_SetBits(GPIOx,GPIO_Pin);
    else
        GPIO_ResetBits(GPIOx,GPIO_Pin);
}

void Class_GPIO::PinLock(GPIO_TypeDef* GPIO, uint16_t GPIO_Pin){
    GPIO_PinLockConfig(GPIO, GPIO_Pin);
}

void Class_GPIO::Tip(void){
    while(1);
}


///////////////////////////////////////////////////////////////////////////////

void _GPIO_Config(
    GPIO_TypeDef* GPIOx,
    uint32_t GPIO_Pin,
    GPIOMode_TypeDef GPIO_Mode,
    GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType,
    GPIOPuPd_TypeDef GPIO_PuPd
) {
    GPIO_InitTypeDef Temp;
		Temp.GPIO_Mode = GPIO_Mode;
		Temp.GPIO_Pin = GPIO_Pin;
        Temp.GPIO_Speed = GPIO_Speed;
        Temp.GPIO_OType = GPIO_OType;
        Temp.GPIO_PuPd = GPIO_PuPd;
    GPIO_Init(GPIOx, &Temp);
}
void _GPIO_Clock(uint32_t RCC_AHB1Periph, FunctionalState NewState) {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph,NewState);
}
void _GPIO_PinLock(GPIO_TypeDef* GPIO, uint16_t GPIO_Pin){
    GPIO_PinLockConfig(GPIO, GPIO_Pin);
}
void _GPIO_SetBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState) {
    if(NewState)
        GPIO_SetBits(GPIOx,GPIO_Pin);
    else
        GPIO_ResetBits(GPIOx,GPIO_Pin);
}

