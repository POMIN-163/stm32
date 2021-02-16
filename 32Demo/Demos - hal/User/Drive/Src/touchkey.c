#include "touchkey.h"

static int8_t statusLast = 0;      // �ϴΰ���״̬
static int8_t statusNow  = 0;      // ���а���״̬ (1 Ϊ����)
volatile uint16_t touchDefult = 0; // ������������ֵ
uint8_t touchkeyFlag = 0;          // ����������־λ
void (*touchkeyFun)(void);         // ����������Ӧ����

void touchRst(void);
uint16_t touchGet(void);
uint16_t touchGetAve(uint8_t times);
uint16_t touchGetMax(uint8_t times);
/**
 * @brief ����������ʼ��
 *
**/
void touchInit(void) {
    uint16_t buff[10];
    uint8_t i;
    gpioAFConf(KEY_TOUCH, GPIO_High_Speed, GPIO_OType_PP, GPIO_PuPd_NOPULL,
               GPIO_AF_TIM2);
    timCapInit(TIM2, 84, 0xffffffff, TIM_CounterMode_Up, TIM_CKD_DIV1,
               TIM_Channel_1, TIM_ICPolarity_Rising, TIM_ICSelection_DirectTI,
               TIM_ICPSC_DIV1, 0x00);
    for ( i = 0; i < 10; i++) {
        buff[i] = touchGet();
        sysDelayMS(10);
    }
    sortBubble16((int16_t*)buff, 10, 0);
    for ( i = 2; i < 8; i++) {
        touchDefult += buff[i];
    }
    for ( i = 0; i < 10; i++) {
        printf(" %d ", buff[i]);
    }
    touchDefult /= 6;
    // printf("touchDefult: %d\r\n",touchDefult);
    statusLast = statusNow = 0;
}
/**
 * @brief ��������ɨ��
 *
**/
#define TOUCH_GATE_VAL 10  // ����ֵ (���� default �ĳ̶�)

void touchScan(void) {
    uint8_t times = 3;     // ��������
    int16_t val = 0;
    if(touchkeyFlag == 0) {
        statusLast = statusNow;
        if(touchkeyFlag == 0) {
            val = touchGetAve(times);
            val = touchGetMax(times);
        }
        if(funAbs(val - touchDefult) > TOUCH_GATE_VAL) {
            statusNow = 1;
        } else {
            statusNow = 0;
        }
        if(!statusNow && statusLast) {   // �ɿ�����Ӧ
            // printf("val: %d\r\n", val);
            touchkeyFlag = 1;
        }
    }
}
/**
 * @brief ����������Ӧ
 *
**/
void touchRun(void) {
    if(touchkeyFlag == 1) {
        if(touchkeyFun != _NULL_) {
            touchkeyFun();
        }
        touchkeyFlag = 0;
    }
}
// �õ�times�ε��ݳ���ƽ��ֵ
uint16_t touchGetAve(uint8_t times) {
    uint8_t i;
    uint16_t result = 0;
    for ( i = 0; i < times; i++) {
        result += touchGet();
    }
    return result / times;
}
// �õ�times�ε��ݳ������ֵ
uint16_t touchGetMax(uint8_t times) {
    uint8_t i;
    uint16_t result = 0;
    uint16_t temp = 0;
    for ( i = 0; i < times; i++) {
        temp = touchGet();
        result = (temp > result) ? temp : result;
    }
    return result;
}
// �õ�һ�ε��ݳ���ֵ
uint16_t touchGet(void) {
    touchRst();
    while(TIM_GetFlagStatus(TIM2, TIM_IT_CC1) == RESET) {
        if(TIM_GetCounter(TIM2) > 0xfffff) {
            // 1 s ��ʱ
            return TIM_GetCounter(TIM2);
        }
    }
    return TIM_GetCapture1(TIM2);
}
// ���ݷŵ�
void touchRst(void) {
    gpioConf(KEY_TOUCH, GPIO_High_Speed, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN);
    gpioOutputSet(KEY_TOUCH, 0);
    sysDelayMS(5);
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1 | TIM_IT_Update);
    TIM_SetCounter(TIM2, 0);
    gpioConf(KEY_TOUCH, GPIO_High_Speed, GPIO_Mode_AF, GPIO_OType_PP,
             GPIO_PuPd_NOPULL);
}
