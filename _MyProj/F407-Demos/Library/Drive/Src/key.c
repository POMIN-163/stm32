#include "key.h"

Func keyFun[allNum];               // 按键响应函数

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
            if (keyFun[buttonNum] != _NULL_) keyFun[buttonNum]();   // 触发单击事件函数
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
 * @brief 按键"对象"初始化
 *
**/
void keyInit(void) {
    uint8_t i;
    gpioConf(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, GPIO_Speed_100MHz,
             GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_UP);
    gpioConf(KEY_UP, GPIO_High_Speed, GPIO_Mode_IN, GPIO_OType_OD,
             GPIO_PuPd_DOWN);
    button_init(&keyObj[0], keyScan_0, 0);    // 初始化 button 对象
    button_init(&keyObj[1], keyScan_1, 0);
    button_init(&keyObj[2], keyScan_2, 0);
    button_init(&keyObj[3], keyScan_3, 1);
    for(i = allNum; i > 0; i--) {
        button_attach(&keyObj[i - 1], SINGLE_CLICK,     keyCall); // 注册回调
        button_attach(&keyObj[i - 1], DOUBLE_CLICK,     keyCall);
        button_attach(&keyObj[i - 1], LONG_PRESS_START, keyCall);
        button_attach(&keyObj[i - 1], LONG_PRESS_HOLD,  keyCall);
        button_start(&keyObj[i - 1]);                             // 启动 button (单链表头尾相连)
    }
}
/**
 * @brief 按键响应
 *
**/
void keyRun(void) {
}
/**
 * @brief 按键扫描
 *
**/
void keyScan(void) {
    button_ticks();
}
#else

static int8_t statusLast[allNum];  // 上次按键状态
static int8_t statusNow[allNum];   // 现行按键状态

uint8_t keyFlag[allNum];           // 按键响应标志位 0.按键扫描, 1.等待响应执行完毕,

/**
 * @brief 按键初始化
 *
**/
#define KEY_UP_MODE 1  // 1 为设置 KEY_UP 按键为 外部中断, 0 为输入捕获

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
 * @brief 按键响应
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
 * @brief 按键扫描
 *
**/
void keyScan(void) {
    uint16_t i;
    // 3个普通按键扫描
    for (i = 0; i < keyNum; i++) {
        statusLast[i] = statusNow[i];
    }
    statusNow[0] = !gpioInputRead(KEY0);      // 因为这三个按键为上拉, 按下为低电平, 估取反
    statusNow[1] = !gpioInputRead(KEY1);
    statusNow[2] = !gpioInputRead(KEY2);
    for (i = 0; i < keyNum; i++) {
        if (statusNow[i] && !statusLast[i]) { // 1 为按下, 0为放开, 松开后响应
            keyFlag[i] = 1;                   // 置标志位
        }
    }
}
// 中断
#define KEY_EXTI0_FLAG keyFlag[KEY_EXTI0]
void EXTI0_IRQHandler(void) {
    if(KEY_EXTI0_FLAG == 0) {
        if (EXTI_GetITStatus(EXTI_Line0) == SET) {
            KEY_EXTI0_FLAG = 1;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}
/***************************** 按键本身会产生抖动, 输入捕获并不靠谱 *********************************/
#define RISING  1
#define FALLING 0
#define KEY_RESPONSE RISING           // 按键按下中断的方式 (上升沿或下降沿触发)
#define KEY_CAP_FLAG keyFlag[KEY_CAP]

uint64_t captureValue = 0;            // 输入捕获值(TIM2/TIM5是32位)
uint32_t captureTime[2] = {0,0};

void reportCap(void) {
    printf("VAL:%d ms %d us\r\n", captureTime[1], captureTime[0]);
}
void TIM5_IRQHandler(void) {
    if(KEY_CAP_FLAG == 0) {                    // 等待响应事件完成再继续捕获
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {  // 溢出 (理论上按键不会按下4000+秒)
            TIM_Cmd(TIM5, DISABLE);
            TIM_SetCounter(TIM5, 0);
            if(statusNow[KEY_CAP] == 1) {
                captureValue += 0XFFFFFFFF;                   // 算上溢出的计数值
            }
            TIM_Cmd(TIM5, ENABLE);
        }
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) {     // 捕获1发生捕获事件 (按键按下或放开)
            statusLast[KEY_CAP] = statusNow[KEY_CAP];
            switch(statusLast[KEY_CAP]) {
            case 0 :                                    // 之前是放开
                TIM_Cmd(TIM5, DISABLE);
                TIM_SetCounter(TIM5, 0);
                captureValue = 0;
                #if(RISING == KEY_RESPONSE)             // 如果按键按下是上升沿
                    TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);
                #else
                    TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);
                #endif
                statusNow[KEY_CAP] = 1;                 // 本次是按下
                TIM_Cmd(TIM5, ENABLE);                  // 开始捕获
                break;
            case 1 :                                    // 之前是按下
                TIM_Cmd(TIM5, DISABLE);
                #if(RISING == KEY_RESPONSE)
                    TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);
                #else
                    TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);
                #endif
                captureValue = TIM_GetCapture1(TIM5);   // 捕获完成
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


