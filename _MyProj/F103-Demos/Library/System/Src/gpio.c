#include "gpio.h"
/**
 * @brief GPIO ��������
 *
 * @param GPIOx      IO �˿ں�
 * @param GPIO_Pin   IO �ܽź�
 * @param GPIO_Speed IO �ٶȴ�С
 * @param GPIO_Mode  IO ģʽ
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
 * @brief �������������ƽ
 *
 * @param GPIOx    IO �˿ں�
 * @param GPIO_Pin IO �ܽź�
 * @param NewState ��ƽֵ
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
 * @brief �����������ƽ
 *
 * @param GPIOx    IO �˿ں�
 * @param GPIO_Pin IO �ܽź�
 * @return uint8_t ������ƽֵ
**/
uint8_t gpioInputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    return (GPIOx->IDR & GPIO_Pin) && 1;
}
uint8_t gpioOutputRead(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    return (GPIOx->ODR & GPIO_Pin) && 1;
}
/**
 * @brief ��ת���������ƽ
 *
 * @param GPIOx    IO �˿ں�
 * @param GPIO_Pin IO �ܽź�
**/
void gpioInputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    GPIOx->IDR ^= GPIO_Pin;
}
void gpioOutputToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    GPIOx->ODR ^= GPIO_Pin;
}
/**
 * @brief IO ��������
 *
 * @param GPIOx      IO �˿ں�
 * @param GPIO_Pin   IO �ܽź�
 * @param GPIO_Speed IO �ٶ�
 * @param GPIO_OType ���ģʽ
 * @param GPIO_PuPd  ����������
 * @param GPIO_AF    ���ù���

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

