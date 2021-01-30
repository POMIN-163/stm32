#include "beep.h"

void beepInit(void) {
    gpioConf(BEEP, GPIO_High_Speed, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN);
}
void beepOn(void) {
    gpioOutputSet(BEEP, 1);
}
void beepOff(void) {
    gpioOutputSet(BEEP, 0);
}
