#include "led.h"

#define LED_IO GPIOF, GPIO_Pin_10

void ledInit(void) {
    gpioConf(LED_IO, GPIO_Speed_100MHz,
        GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP);
}
void ledToggle(void) {
    LED = !LED;
}
void ledOn(void) {
    LED = 0;
}
void ledOff(void) {
    LED = 1;
}
