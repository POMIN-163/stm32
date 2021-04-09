#include "hc_sr04.h"
// ���������ģ��
static u16 msHcCount = 0;  //ms����

void hcsr04Init(void) {
    gpioConf(TRIG, GPIO_High_Speed, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP);
    gpioOutputSet(TRIG, 0);
    gpioConf(ECHO, GPIO_High_Speed, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL);
    gpioInputSet(ECHO, 0);
    timBaseConf(HC_TIM, 72, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(HC_IRQ, 0x01, 0x03);
    TIM_ClearFlag(HC_TIM, TIM_FLAG_Update);
}
//�򿪶�ʱ��
static void OpenTimerForHc() {
    TIM_SetCounter(HC_TIM,0);      // �������
    msHcCount = 0;
    TIM_Cmd(HC_TIM, ENABLE);
}
//�رն�ʱ��
static void CloseTimerForHc() {
    TIM_Cmd(HC_TIM, DISABLE);
}
//��ȡ��ʱ��ʱ��
static u32 GetEchoTimer(void) {
    u32 t = 0;
    t = msHcCount*1000;            // �õ�MS
    t += TIM_GetCounter(HC_TIM);   // �õ�US
    HC_TIM->CNT = 0;
        sysDelayMS(50);
    return t;
}
// һ�λ�ȡ������������� ���β��֮����Ҫ���һ��ʱ�䣬���ϻ����ź�
// Ϊ�����������Ӱ�죬ȡ������ݵ�ƽ��ֵ���м�Ȩ�˲���
uint32_t hcsr04GetLength(void) {
    u32 t = 0;
    int i = 0;
    float lengthTemp = 0;
    float sum = 0;
    while(i!=5) {
        gpioInputSet(TRIG, 1);
        sysDelayUS(20);
        gpioInputSet(TRIG, 0);
        while(gpioInputRead(ECHO) == 0);   // �ȴ����տڸߵ�ƽ���
        OpenTimerForHc();                  // �򿪶�ʱ��
        i = i + 1;
        while(gpioInputRead(ECHO) == 1);
        CloseTimerForHc();                 // �رն�ʱ��
        t = GetEchoTimer();                // ��ȡʱ��,�ֱ���Ϊ1US
        lengthTemp = ((float)t/(float)58.0 * (float)10.0); // mm
        sum = lengthTemp + sum;
    }
    lengthTemp = sum/(float)5.0;
    return (uint32_t)lengthTemp;
}
// TIM9 �ж�
void TIM1_BRK_TIM9_IRQHandler(void) {
    if (TIM_GetITStatus(HC_TIM, TIM_IT_Update) != RESET) {
        msHcCount++;
        TIM_ClearITPendingBit(HC_TIM, TIM_IT_Update);
    }
}
