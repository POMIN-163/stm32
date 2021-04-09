#include "ec11.h"

uint8_t ec11StatusNow  = 1;
uint8_t ec11StatusLast = 1;

void ec11Init(void) {
    uint8_t i;
    gpioConf(EC11A, GPIO_Speed_10MHz, GPIO_Mode_IPU);
    gpioConf(EC11B, GPIO_Speed_10MHz, GPIO_Mode_IPU);
    GPIO_ResetBits(EC11A);
    GPIO_ResetBits(EC11B);
}
void ec11Scan(uint8_t *msg) {
    ec11StatusLast = ec11StatusNow;
    // 读取当前按键状态
    ec11StatusNow = EC11_A;
    // 检测到按键按下之后并放开置位标志位
    if (!ec11StatusNow && ec11StatusLast) {
        if (EC11_B) {
            if (!(*msg))
                *msg = 2;
        }
        else {
            if (!(*msg))
                *msg = 1;
        }
    }
}
void ec11Run(void) {

}