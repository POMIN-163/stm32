#include "key.h"

Func keyFun[allNum];               // ������Ӧ����

#if 1 == USE_MULTIBUTTON
Button keyObj[allNum];

uint8_t keyScan_0(void) { return gpioInputRead(KEY0); }
uint8_t keyScan_1(void) { return gpioInputRead(KEY1); }
uint8_t keyScan_2(void) { return gpioInputRead(KEY2); }
uint8_t keyScan_3(void) { return gpioInputRead(KEY_UP); }

void keyCall(void *button) {
    uint32_t btn_event_val;
    btn_event_val = get_button_event((struct Button *)button);
    switch(btn_event_val) {
        /*case PRESS_REPEAT:
            printLog("---> key1 press repeat%d! <---", ((struct Button *)button)->repeat);
            break;*/
        case SINGLE_CLICK:
            printLog("---> key%d single click! <---", buttonNum);
            if (keyFun[buttonNum] != _NULL_) keyFun[buttonNum]();   // ���������¼�����
            break;
        case DOUBLE_CLICK:
            printLog("***> key%d double click! <***", buttonNum);
            break;
        case LONG_PRESS_START:
            printLog("---> key%d long press start! <---", buttonNum);
            break;
        case LONG_PRESS_HOLD:
            printLog("***> key%d long press hold! <***", buttonNum);
            break;
    }
}
/**
 * @brief ����"����"��ʼ��
 *
**/
void keyInit(void) {
    uint8_t i;
    gpioConf(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, GPIO_Speed_100MHz,
             GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_UP);
    gpioConf(KEY_UP, GPIO_High_Speed, GPIO_Mode_IN, GPIO_OType_OD,
             GPIO_PuPd_DOWN);
    button_init(&keyObj[0], keyScan_0, 0);    // ��ʼ�� button ����
    button_init(&keyObj[1], keyScan_1, 0);
    button_init(&keyObj[2], keyScan_2, 0);
    button_init(&keyObj[3], keyScan_3, 1);
    for(i = allNum; i > 0; i--) {
        button_attach(&keyObj[i - 1], SINGLE_CLICK,     keyCall); // ע��ص�
        button_attach(&keyObj[i - 1], DOUBLE_CLICK,     keyCall);
        button_attach(&keyObj[i - 1], LONG_PRESS_START, keyCall);
        button_attach(&keyObj[i - 1], LONG_PRESS_HOLD,  keyCall);
        button_start(&keyObj[i - 1]);                             // ���� button (������ͷβ����)
    }
}
/**
 * @brief ������Ӧ
 *
**/
void keyRun(void) {
}
/**
 * @brief ����ɨ��
 *
**/
void keyScan(void) {
    button_ticks();
}
#else

static int8_t statusLast[allNum];  // �ϴΰ���״̬
static int8_t statusNow[allNum];   // ���а���״̬

uint8_t keyFlag[allNum];           // ������Ӧ��־λ 0.����ɨ��, 1.�ȴ���Ӧִ�����,

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
// �ж�
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

void reportCap(void) {
    printf("VAL:%d ms %d us\r\n", captureTime[1], captureTime[0]);
}
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
#endif


