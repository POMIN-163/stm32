#include "gpio.h"
/**
 * @brief GPIO ��������
 *
 * @param GPIOx      IO �˿ں�
 * @param GPIO_Pin   IO �ܽź�
 * @param GPIO_Speed IO �ٶȴ�С
 * @param GPIO_Mode  IO ģʽ
 * @param GPIO_OType ���ģʽ
 * @param GPIO_PuPd  ����������
**/
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
	case GPIOH_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN; break;
	case GPIOI_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN; break;
	case GPIOJ_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN; break;
	case GPIOK_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN; break;
	default: break;
	}
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed;
    GPIO_InitStruct.GPIO_OType = GPIO_OType;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd;
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
**/
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
