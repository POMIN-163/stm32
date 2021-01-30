#include "device.h"
#include "pominLib.h"

uint32_t gTime = 0;

void test1(void){
    printf("exti0\r\n");
}
void test(void){
    beepOn();
    sysDelayMS(500);
    beepOff();
}
void Init() {
    nvicGroupConf(NVIC_PriorityGroup_2);
    sysConf(168, 1);
    ledInit();
    keyInit();
    beepInit();
    hcsr04Init();
    breathLedInit();
    uart_init(115200);
    keyFun[0] = test;
    extiFun[0] = test1;
}
int main(void) {
    Init();
    while(1) {
        ledToggle(LED1);
        keyScan();
        sysDelayMS(500);
        printf("Status: %d, %d\r\n", gpioOutputRead(LED1), gpioInputRead(KEY1));
        printf("Distance: %d\r\n", hcsr04GetLength());
    }
}
