#ifndef __WS2812B_H
#define __WS2812B_H

#include "system.h"

#define WS2812B_IO GPIOA, GPIO_Pin_11
#define WS2812B PAout(11)
// WS2812B 信号管脚
#define RGB_NUM 12
// 灯珠个数

typedef struct {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} RGB;

void rgbInit(void);
void rgbWrite_One(uint8_t red, uint8_t green, uint8_t blue);
void rgbAll(uint8_t red, uint8_t green, uint8_t blue);

#endif




