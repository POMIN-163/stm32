#include "hc_sr04.h"
// 超声波测距模块
static u16 msHcCount = 0;  //ms计数

void hcsr04Init(void) {
    gpioConf(TRIG, GPIO_High_Speed, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP);
    gpioOutputSet(TRIG, 0);
    gpioConf(ECHO, GPIO_High_Speed, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL);
    gpioInputSet(ECHO, 0);
    timBaseConf(HC_TIM, 72, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(HC_IRQ, 0x01, 0x03);
    TIM_ClearFlag(HC_TIM, TIM_FLAG_Update);
}
//打开定时器
static void OpenTimerForHc() {
    TIM_SetCounter(HC_TIM,0);      // 清除计数
    msHcCount = 0;
    TIM_Cmd(HC_TIM, ENABLE);
}
//关闭定时器
static void CloseTimerForHc() {
    TIM_Cmd(HC_TIM, DISABLE);
}
//获取定时器时间
static u32 GetEchoTimer(void) {
    u32 t = 0;
    t = msHcCount*1000;            // 得到MS
    t += TIM_GetCounter(HC_TIM);   // 得到US
    HC_TIM->CNT = 0;
        sysDelayMS(50);
    return t;
}
// 一次获取超声波测距数据 两次测距之间需要相隔一段时间，隔断回响信号
// 为了消除余震的影响，取五次数据的平均值进行加权滤波。
uint32_t hcsr04GetLength(void) {
    u32 t = 0;
    int i = 0;
    float lengthTemp = 0;
    float sum = 0;
    while(i!=5) {
        gpioInputSet(TRIG, 1);
        sysDelayUS(20);
        gpioInputSet(TRIG, 0);
        while(gpioInputRead(ECHO) == 0);   // 等待接收口高电平输出
        OpenTimerForHc();                  // 打开定时器
        i = i + 1;
        while(gpioInputRead(ECHO) == 1);
        CloseTimerForHc();                 // 关闭定时器
        t = GetEchoTimer();                // 获取时间,分辨率为1US
        lengthTemp = ((float)t/(float)58.0 * (float)10.0); // mm
        sum = lengthTemp + sum;
    }
    lengthTemp = sum/(float)5.0;
    return (uint32_t)lengthTemp;
}
// TIM9 中断
void TIM1_BRK_TIM9_IRQHandler(void) {
    if (TIM_GetITStatus(HC_TIM, TIM_IT_Update) != RESET) {
        msHcCount++;
        TIM_ClearITPendingBit(HC_TIM, TIM_IT_Update);
    }
}
