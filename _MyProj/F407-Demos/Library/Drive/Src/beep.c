#include "beep.h"

#define BEEP_IO GPIOF, GPIO_Pin_8

void beepInit(void) {
    gpioConf(BEEP_IO, GPIO_High_Speed, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN);
}
void beepOn(void) {
    BEEP = 1;
}
void beepOff(void) {
    BEEP = 0;
}
void beepOnce(uint16_t nms) {
    BEEP = 1;
    if(nms > 10000) sysDelayMS(200); // Êý¾ÝÒì³£
    else sysDelayMS(nms);
    BEEP = 0;
}
