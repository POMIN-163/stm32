#include "Class_GPIO.h"
#include "stm32f4xx.h"

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
void Class_GPIO::Config_AF(
    GPIO_TypeDef* GPIOx,
    uint32_t GPIO_Pin,
    uint16_t GPIO_PinSource,
    GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType,
    GPIOPuPd_TypeDef GPIO_PuPd,
    uint8_t GPIO_AF
) {
    GPIO_InitTypeDef Temp={GPIO_Pin, GPIO_Mode_AF, GPIO_Speed, GPIO_OType, GPIO_PuPd};
    GPIO_Init(GPIOx, &Temp);
    GPIO_PinAFConfig(GPIOx,GPIO_PinSource,GPIO_AF);
}

//***以下是C语言调用函数***//

void _GPIO_Config(
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
void _GPIO_Clock(uint32_t RCC_AHB1Periph, FunctionalState NewState) {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph,NewState);
}
void _GPIO_SetBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState) {
    if(NewState)
        GPIO_SetBits(GPIOx,GPIO_Pin);
    else
        GPIO_ResetBits(GPIOx,GPIO_Pin);
}
void _GPIO_Config_AF(
    GPIO_TypeDef* GPIOx,
    uint32_t GPIO_Pin,
    uint16_t GPIO_PinSource,
    GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType,
    GPIOPuPd_TypeDef GPIO_PuPd,
    uint8_t GPIO_AF
) {
    GPIO_InitTypeDef Temp={GPIO_Pin, GPIO_Mode_AF, GPIO_Speed, GPIO_OType, GPIO_PuPd};
    GPIO_Init(GPIOx, &Temp);
    GPIO_PinAFConfig(GPIOx,GPIO_PinSource,GPIO_AF);
}


