#include "gpio.h"

void gpioConf(
    GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed,
    GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd
) {
    GPIO_InitTypeDef GPIO_InitStruct;
	switch ((uint32_t)GPIOx)
	{
	case GPIOA_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; break;
	case GPIOB_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; break;
	case GPIOC_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; break;
	case GPIOD_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; break;
	case GPIOE_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; break;
	case GPIOF_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; break;
	case GPIOG_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; break;
	default: break;
	}
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed;
    GPIO_InitStruct.GPIO_OType = GPIO_OType;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd;
    GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void gpioInputSet(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState) {
    if(NewState)
        GPIO_SetBits(GPIOx, GPIO_Pin);
    else
        GPIO_ResetBits(GPIOx, GPIO_Pin);
}
void gpioOutputSet(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t NewState) {
    if(NewState)
        GPIO_SetBits(GPIOx, GPIO_Pin);
    else
        GPIO_ResetBits(GPIOx, GPIO_Pin);
}
uint8_t gpioInputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    return (GPIOx->IDR & GPIO_Pin) && 1;
}
uint8_t gpioOutputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    return (GPIOx->ODR & GPIO_Pin) && 1;
}
void gpioInputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    GPIOx->IDR ^= GPIO_Pin;
}
void gpioOutputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    GPIOx->ODR ^= GPIO_Pin;
}
void gpioAFConf(
    GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd, uint8_t GPIO_AF
) {
    uint8_t i;
    GPIO_InitTypeDef GPIO_InitStruct;
    uint16_t GPIO_PinSource;
	switch ((uint32_t)GPIOx)
	{
	case GPIOA_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; break;
	case GPIOB_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; break;
	case GPIOC_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; break;
	case GPIOD_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; break;
	case GPIOE_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; break;
	case GPIOF_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; break;
	case GPIOG_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; break;
	case GPIOH_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN; break;
	case GPIOI_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN; break;
	case GPIOJ_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN; break;
	case GPIOK_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN; break;
	default: break;
	}
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed;
    GPIO_InitStruct.GPIO_OType = GPIO_OType;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd;
    for ( i = 0; i < 16; i++) {
        if((0x01 << i) == GPIO_Pin) GPIO_PinSource = i;
    }
    GPIO_PinAFConfig(GPIOx, GPIO_PinSource, GPIO_AF);

    GPIO_Init(GPIOx, &GPIO_InitStruct);
}
