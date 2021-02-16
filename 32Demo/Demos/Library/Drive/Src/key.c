#include "key.h"

// keyFlag: 0.����ɨ��, 1.�ȴ���Ӧִ�����,

static int8_t statusLast[allNum];  // �ϴΰ���״̬
static int8_t statusNow[allNum];   // ���а���״̬

uint8_t keyFlag[allNum];           // ������Ӧ��־λ
void (*keyFun[allNum])(void);      // ������Ӧ����
/**
 * @brief ������ʼ��
 *
**/
#define KEY_UP_MODE 1  // 1 Ϊ���� KEY_UP ����Ϊ �ⲿ�ж�, 0 Ϊ���벶��

void keyInit(void) {
    uint16_t i;
    gpioConf(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, GPIO_Speed_100MHz,
             GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_UP);
#if 1 == KEY_UP_MODE
    gpioConf(KEY_UP, GPIO_High_Speed, GPIO_Mode_IN, GPIO_OType_OD,
             GPIO_PuPd_DOWN);
    extiConf(EXTI_PortSourceGPIOA, EXTI_PinSource0, EXTI_Line0,
             EXTI_Mode_Interrupt, EXTI_Trigger_Rising);
    nvicIRQConf(EXTI0_IRQn, 0x01, 0x02);
#else
    gpioAFConf(KEY_UP, GPIO_High_Speed, GPIO_OType_PP, GPIO_PuPd_DOWN,
               GPIO_AF_TIM5);
    timCapInit(TIM5, 84, 0xffffffff, TIM_CounterMode_Up, TIM_CKD_DIV1,
               TIM_Channel_1, TIM_ICPolarity_Rising, TIM_ICSelection_DirectTI,
               TIM_ICPSC_DIV1, 0x00);
    nvicIRQConf(TIM5_IRQn, 0x02, 0x00);
#endif
    for (i = 0; i < allNum; i++) {
        statusLast[i] = statusNow[i] = 0;
    }
}
/**
 * @brief ������Ӧ
 *
**/
void keyRun(void) {
    uint8_t i;
    for (i = 0; i < allNum; i++) {
        if(keyFlag[i] == 1) {
            if (keyFun[i] != _NULL_) {
                keyFun[i]();
            }
            keyFlag[i] = 0;
        }
    }
}
/**
 * @brief ����ɨ��
 *
**/
void keyScan(void) {
    uint16_t i;
    // 3����ͨ����ɨ��
    for (i = 0; i < keyNum; i++) {
        statusLast[i] = statusNow[i];
    }
    statusNow[0] = !gpioInputRead(KEY0);      // ��Ϊ����������Ϊ����, ����Ϊ�͵�ƽ, ��ȡ��
    statusNow[1] = !gpioInputRead(KEY1);
    statusNow[2] = !gpioInputRead(KEY2);
    for (i = 0; i < keyNum; i++) {
        if (statusNow[i] && !statusLast[i]) { // 1 Ϊ����, 0Ϊ�ſ�, �ɿ�����Ӧ
            keyFlag[i] = 1;                   // �ñ�־λ
        }
    }
}

#define KEY_EXTI0_FLAG keyFlag[KEY_EXTI0]
void EXTI0_IRQHandler(void) {
    if(KEY_EXTI0_FLAG == 0) {
        if (EXTI_GetITStatus(EXTI_Line0) == SET) {
            KEY_EXTI0_FLAG = 1;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}
/***************************** ����������������, ���벶�񲢲����� *********************************/
#define RISING  1
#define FALLING 0
#define KEY_RESPONSE RISING           // ���������жϵķ�ʽ (�����ػ��½��ش���)
#define KEY_CAP_FLAG keyFlag[KEY_CAP]

uint64_t captureValue = 0;            // ���벶��ֵ(TIM2/TIM5��32λ)
uint32_t captureTime[2] = {0,0};

void TIM5_IRQHandler(void) {
    if(KEY_CAP_FLAG == 0) {                    // �ȴ���Ӧ�¼�����ټ�������
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {  // ��� (�����ϰ������ᰴ��4000+��)
            TIM_Cmd(TIM5, DISABLE);
            TIM_SetCounter(TIM5, 0);
            if(statusNow[KEY_CAP] == 1) {
                captureValue += 0XFFFFFFFF;                   // ��������ļ���ֵ
            }
            TIM_Cmd(TIM5, ENABLE);
        }
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) {     // ����1���������¼� (�������»�ſ�)
            statusLast[KEY_CAP] = statusNow[KEY_CAP];
            switch(statusLast[KEY_CAP]) {
            case 0 :                                    // ֮ǰ�Ƿſ�
                TIM_Cmd(TIM5, DISABLE);
                TIM_SetCounter(TIM5, 0);
                captureValue = 0;
                #if(RISING == KEY_RESPONSE)             // �������������������
                    TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);
                #else
                    TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);
                #endif
                statusNow[KEY_CAP] = 1;                 // �����ǰ���
                TIM_Cmd(TIM5, ENABLE);                  // ��ʼ����
                break;
            case 1 :                                    // ֮ǰ�ǰ���
                TIM_Cmd(TIM5, DISABLE);
                #if(RISING == KEY_RESPONSE)
                    TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);
                #else
                    TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);
                #endif
                captureValue = TIM_GetCapture1(TIM5);   // �������
                statusNow[KEY_CAP] = 0;
                TIM_Cmd(TIM5, ENABLE);
                break;
            }
            if(statusLast[KEY_CAP] && !statusNow[KEY_CAP]) {
                statusLast[KEY_CAP] = statusNow[KEY_CAP] = 0;
                KEY_CAP_FLAG = 1;
            }
        }
    }
    captureTime[0] = captureValue%1000;
    captureTime[1] = captureValue/1000;
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update);
}
