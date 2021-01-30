#include "key.h"

static int8_t statusLast[keyNum];
static int8_t statusNow[keyNum];
static int8_t keyMsg = 0;

void(*keyFun[keyNum])(void);    // 普通按键按下的响应函数
void(*extiFun[extiNum])(void);  // 外部中断按键按下的响应函数

void keyInit(void) {
    uint16_t i;
    gpioConf(GPIOE, GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4, GPIO_Speed_100MHz,
        GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_UP);
    gpioConf(GPIOA, GPIO_Pin_0, GPIO_Speed_100MHz,
        GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL);
    /*
    extiConf(EXTI_PortSourceGPIOA, EXTI_PinSource0, EXTI_Line0, EXTI_Mode_Interrupt, EXTI_Trigger_Rising);
    nvicIRQConf(EXTI0_IRQn, 0x01, 0x02);
    for ( i = 0; i < keyNum; i++) {
        statusLast[i] = statusNow[i] = 1;
    }
    */
}
void keyScan(void) {
    uint16_t i;
    for ( i = 0; i < keyNum; i++) {
        statusLast[i] = statusNow[i];
    }
    statusNow[0] = gpioInputRead(KEY0);
    statusNow[1] = gpioInputRead(KEY1);
    statusNow[2] = gpioInputRead(KEY2);
    for(i = 0; i < keyNum; i++) {
        if( statusNow[i] && !statusLast[i]) {    // 上拉时放开响应, 下拉时按下响应
            keyMsg = i+1;
        }
    }
    if(keyMsg && (keyFun[keyMsg-1] != _NULL_)) {
        keyFun[keyMsg - 1]();
        keyMsg = 0;
    }
}
void EXTI0_IRQHandler(void) {
    if(EXTI_GetITStatus(EXTI_Line0) == SET) {
        while(gpioInputRead(KEY_UP));
        if(extiFun[0] != _NULL_) extiFun[0]();
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
