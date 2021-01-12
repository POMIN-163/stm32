#ifndef __WS2812B_H
#define __WS2812B_H

#include "delay.h"

#define WS2810B_GPIO GPIOA
#define WS2812B_PIN GPIO_Pin_11
#define WS2812B_CLK RCC_APB2Periph_GPIOA
#define WS2812B_PIN_H (GPIO_SetBits(WS2810B_GPIO, WS2812B_PIN))
#define WS2812B_PIN_L (GPIO_ResetBits(WS2810B_GPIO, WS2812B_PIN))
// WS2812B 信号管脚
#define LED_NUM 30
// 灯珠个数

typedef struct {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} RGB;


void WS2812B_Init(void);
void WS2812B_Reset(void);
void WS2812B_Write_24Bits(uint8_t red, uint8_t green, uint8_t blue);
void WS2812B_All(uint8_t red, uint8_t green, uint8_t blue);

void WS2812B_Write_24Bits_RGB(RGB *color);
void WS2812B_All_RGB(RGB *color);

#endif




