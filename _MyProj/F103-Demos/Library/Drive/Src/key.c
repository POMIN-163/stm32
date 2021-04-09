#include "key.h"

Func keyFun[allNum];               // 按键响应函数

#if 1 == USE_MULTIBUTTON
Button keyObj[allNum];

uint8_t keyScan_0(void) { return gpioInputRead(KEY0); }
uint8_t keyScan_1(void) { return gpioInputRead(KEY1); }

void keyCall(void *button) {
    uint32_t btn_event_val;
    btn_event_val = get_button_event((struct Button *)button);
    switch(btn_event_val) {
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
    gpioConf(GPIOB, GPIO_Pin_5 | GPIO_Pin_4, GPIO_Speed_10MHz, GPIO_Mode_IPU);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_4);
    button_init(&keyObj[0], keyScan_0, 1);    // 初始化 button 对象
    button_init(&keyObj[1], keyScan_1, 1);
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


#endif

