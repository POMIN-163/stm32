#include "gpio.h"
/**
 * @brief GPIO 基本配置
 *
 * @param GPIOx      IO 端口号
 * @param GPIO_Pin   IO 管脚号
 * @param GPIO_Speed IO 速度大小
 * @param GPIO_Mode  IO 模式
**/
void gpioConf(
    GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed,
    GPIOMode_TypeDef GPIO_Mode
) {
    GPIO_InitTypeDef GPIO_InitStruct;
	switch ((uint32_t)GPIOx)
	{
	case GPIOA_BASE: RCC->APB2ENR |= RCC_APB2Periph_GPIOA; break;
	case GPIOB_BASE: RCC->APB2ENR |= RCC_APB2Periph_GPIOB; break;
	case GPIOC_BASE: RCC->APB2ENR |= RCC_APB2Periph_GPIOC; break;
	case GPIOD_BASE: RCC->APB2ENR |= RCC_APB2Periph_GPIOD; break;
	case GPIOE_BASE: RCC->APB2ENR |= RCC_APB2Periph_GPIOE; break;
	case GPIOF_BASE: RCC->APB2ENR |= RCC_APB2Periph_GPIOF; break;
	case GPIOG_BASE: RCC->APB2ENR |= RCC_APB2Periph_GPIOG; break;
	default: break;
	}
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed;
    GPIO_Init(GPIOx, &GPIO_InitStruct);
}
/**
 * @brief 设置输入输出电平
 *
 * @param GPIOx    IO 端口号
 * @param GPIO_Pin IO 管脚号
 * @param NewState 电平值
**/
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
/**
 * @brief 读输入输出电平
 *
 * @param GPIOx    IO 端口号
 * @param GPIO_Pin IO 管脚号
 * @return uint8_t 读出电平值
**/
uint8_t gpioInputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    return (GPIOx->IDR & GPIO_Pin) && 1;
}
uint8_t gpioOutputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    return (GPIOx->ODR & GPIO_Pin) && 1;
}
/**
 * @brief 反转输入输出电平
 *
 * @param GPIOx    IO 端口号
 * @param GPIO_Pin IO 管脚号
**/
void gpioInputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    GPIOx->IDR ^= GPIO_Pin;
}
void gpioOutputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    GPIOx->ODR ^= GPIO_Pin;
}
/**
 * @brief IO 复用配置
 *
 * @param GPIOx      IO 端口号
 * @param GPIO_Pin   IO 管脚号
 * @param GPIO_Speed IO 速度
 * @param GPIO_OType 输出模式
 * @param GPIO_PuPd  上下拉设置
 * @param GPIO_AF    复用功能

void gpioAFConf(
    GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd, uint8_t GPIO_AF
) {
    uint32_t i;
    gpioConf(GPIOx, GPIO_Pin, GPIO_Speed, GPIO_Mode_AF, GPIO_OType, GPIO_PuPd);
    for ( i = 0; i < 16; i++) {
        if(((0x01 << i) & GPIO_Pin) != 0)
            GPIO_PinAFConfig(GPIOx, i, GPIO_AF);
    }
}
**/

