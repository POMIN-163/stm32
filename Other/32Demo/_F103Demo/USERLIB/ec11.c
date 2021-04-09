#include "ec11.h"

uint8_t ec11StatusNow  = 1;
uint8_t ec11StatusLast = 1;

void ec11Init(void) {
     GPIO_InitTypeDef  GPIO_InitStructure;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_SetBits(EC11A);
    GPIO_SetBits(EC11B);
}
void ec11Scan(uint8_t *msg) {
    uint8_t i;
    ec11StatusLast = ec11StatusNow;
    // 读取当前按键状态
    ec11StatusNow = EC11_A;
    // 检测到按键按下之后并放开置位标志位
    if (!ec11StatusNow && ec11StatusLast) {
        if (EC11_B) {
            PCout(13) = 0;
            delay_ms(500);
            PCout(13) = 1;
        }
        else {
            PCout(13) = 0;
            delay_ms(500);
            PCout(13) = 1;
            delay_ms(500);
            PCout(13) = 0;
            delay_ms(500);
            PCout(13) = 1;
        }
    }
}
void ec11Run(void) {

}

