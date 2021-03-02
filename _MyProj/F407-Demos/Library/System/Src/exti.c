#include "exti.h"
/**
 * @brief �ⲿ�ж�����
 *
 * @param EXTI_Line    �ж���
 * @param EXTI_Mode    �ж�ģʽ
 * @param EXTI_Trigger �жϴ�����ʽ
**/
void extiConf(uint32_t EXTI_Line, EXTIMode_TypeDef EXTI_Mode,
              EXTITrigger_TypeDef EXTI_Trigger
) {
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_ClearITPendingBit(EXTI_Line);
    EXTI_Init(&EXTI_InitStruct);
}

/**
 * @brief GPIO �ⲿ�ж�����
 *
 * @param GPIOx        �˿ں�
 * @param GPIO_Pin     �ܽź�
 * @param EXTI_Line    �ж���
 * @param EXTI_Mode    �ж�ģʽ
 * @param EXTI_Trigger �жϴ�����ʽ
**/
void extiGpioConf(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin,
                  uint32_t EXTI_Line, EXTIMode_TypeDef EXTI_Mode,
                  EXTITrigger_TypeDef EXTI_Trigger
) {
    uint32_t i, j;
    for ( i = 0; i < 16; i++) {
        if (((0x01 << i) & GPIO_Pin) != 0) break;
    }
	switch ((uint32_t)GPIOx)
	{
	case GPIOA_BASE: j = 0; break;
	case GPIOB_BASE: j = 1; break;
	case GPIOC_BASE: j = 2; break;
	case GPIOD_BASE: j = 3; break;
	case GPIOE_BASE: j = 4; break;
	case GPIOF_BASE: j = 5; break;
	case GPIOG_BASE: j = 6; break;
	case GPIOH_BASE: j = 7; break;
	case GPIOI_BASE: j = 8; break;
	case GPIOJ_BASE: j = 9; break;
	case GPIOK_BASE: j = 10;break;
	default:         j = 0; break;
	}
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(j, i);
    extiConf(EXTI_Line, EXTI_Mode, EXTI_Trigger);
}
