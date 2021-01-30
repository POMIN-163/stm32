#include "led.h"

void ledInit(void) {
    gpioConf(LED1, GPIO_Speed_100MHz,
        GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP);
}
void ledToggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    gpioOutputToggle(GPIOx, GPIO_Pin);
}
void ledOn(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    gpioOutputSet(GPIOx, GPIO_Pin, 0);
}
void ledOff(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
    gpioOutputSet(GPIOx, GPIO_Pin, 1);
}
