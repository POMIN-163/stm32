#include "tim.h"
/**
 * @brief ������ʱ������
 *
 * @param TIMx            ��ʱ����
 * @param TIM_Prescaler   ��Ƶϵ��
 * @param TIM_Period      ��װ��ֵ | ������
 * @param TIM_CounterMode ����ģʽ
 * @param TIM_CKD         ʱ�ӷ�Ƶϵ��
 **/
void timBaseConf(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                 uint16_t TIM_CounterMode, uint16_t TIM_CKD) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    switch ((uint32_t)TIMx) {
        case TIM1_BASE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
            break;
        case TIM2_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
            break;
        case TIM3_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
            break;
        case TIM4_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
            break;
        case TIM5_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
            break;
        case TIM6_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
            break;
        case TIM7_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
            break;
        case TIM8_BASE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
            break;
        case TIM9_BASE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
            break;
        case TIM10_BASE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
            break;
        case TIM11_BASE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
            break;
        case TIM12_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
            break;
        case TIM13_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
            break;
        case TIM14_BASE:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
            break;
        default:
            break;
    }
    // ���û�����ʱ��
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD;
    TIM_TimeBaseInitStruct.TIM_Period = TIM_Period - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM_Prescaler - 1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}
/**
 * @brief ��ʱ��PWM����
 *
 * @param TIMx            ��ʱ����
 * @param TIM_Prescaler   ��Ƶϵ��
 * @param TIM_Period      ��װ��ֵ | ������ (PWM ���� = ������ * (1 / PWMƵ��))
 * @param TIM_CounterMode ����ģʽ
 * @param TIM_CKD         ʱ�ӷ�Ƶϵ��
 * @param OCx             ���ͨ����
 * @param TIM_OCMode      ��ʱ��ģʽ
 * @param TIM_OutputState ���ģʽ
 * @param TIM_OCPolarity  �������
 **/
void timPwmConf(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                uint16_t TIM_CounterMode, uint16_t TIM_CKD, OC_TypeDef OCx,
                uint16_t TIM_OCMode, uint16_t TIM_OutputState,
                uint16_t TIM_OCPolarity) {
    TIM_OCInitTypeDef TIM_OCInitStruct;
    // ���û�����ʱ��
    timBaseConf(TIMx, TIM_Prescaler, TIM_Period, TIM_CounterMode, TIM_CKD);
    // ���� PWM �����ͨ��
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity;
    switch (OCx) {
        case OC1:
            TIM_OC1Init(TIMx, &TIM_OCInitStruct);
            TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
            break;
        case OC2:
            TIM_OC2Init(TIMx, &TIM_OCInitStruct);
            TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
            break;
        case OC3:
            TIM_OC3Init(TIMx, &TIM_OCInitStruct);
            TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
            break;
        case OC4:
            TIM_OC4Init(TIMx, &TIM_OCInitStruct);
            TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
            break;
        default:
            break;
    }
    TIM_ARRPreloadConfig(TIMx, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}
/**
 * @brief ��ʱ�����벶������
 *
 * @param TIMx             ��ʱ����
 * @param TIM_Prescaler    ��Ƶϵ��
 * @param TIM_Period       ��װ��ֵ | ������ (���벶�������0xffff ffff(32λ)��0xffff(16λ) ������)
 * @param TIM_CounterMode  ����ģʽ
 * @param TIM_CKD          ʱ�ӷ�Ƶϵ��
 * @param TIM_Channel      ͨ����
 * @param TIM_ICPolarity   ��������
 * @param TIM_ICSelection  ӳ��
 * @param TIM_ICPSC        �����Ƶ
 * @param TIM_ICFilter     �����˲���
 **/
void timCapInit(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                uint16_t TIM_CounterMode, uint16_t TIM_CKD,
                uint16_t TIM_Channel, uint16_t TIM_ICPolarity,
                uint16_t TIM_ICSelection, uint16_t TIM_ICPSC,
                uint16_t TIM_ICFilter) {
    TIM_ICInitTypeDef TIM_ICInitStructure;
    timBaseConf(TIMx, TIM_Prescaler, TIM_Period, TIM_CounterMode, TIM_CKD);
    // ��ʼ�����벶�����
    TIM_ICInitStructure.TIM_Channel = TIM_Channel;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC;
    TIM_ICInitStructure.TIM_ICFilter = TIM_ICFilter;
    TIM_ICInit(TIMx, &TIM_ICInitStructure);
    // �ж�����
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    switch (TIM_Channel) {
        case TIM_Channel_1:
            TIM_ITConfig(TIMx, TIM_IT_CC1, ENABLE);
            break;
        case TIM_Channel_2:
            TIM_ITConfig(TIMx, TIM_IT_CC2, ENABLE);
            break;
        case TIM_Channel_3:
            TIM_ITConfig(TIMx, TIM_IT_CC3, ENABLE);
            break;
        case TIM_Channel_4:
            TIM_ITConfig(TIMx, TIM_IT_CC4, ENABLE);
            break;
    }
    TIM_Cmd(TIMx, ENABLE);
}
