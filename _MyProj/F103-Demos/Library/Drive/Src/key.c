#include "key.h"

Func keyFun[allNum];               // ������Ӧ����

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
    gpioConf(GPIOB, GPIO_Pin_5 | GPIO_Pin_4, GPIO_Speed_10MHz, GPIO_Mode_IPU);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_4);
    button_init(&keyObj[0], keyScan_0, 1);    // ��ʼ�� button ����
    button_init(&keyObj[1], keyScan_1, 1);
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


#endif

