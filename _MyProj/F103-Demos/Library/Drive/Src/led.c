#include "led.h"

#define LED_IO GPIOC, GPIO_Pin_13

void ledInit(void) {
    gpioConf(LED_IO, GPIO_Speed_10MHz,
        GPIO_Mode_Out_PP);
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
