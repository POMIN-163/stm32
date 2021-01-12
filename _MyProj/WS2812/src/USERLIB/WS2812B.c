/****************************************************
 * @Author     		POMIN
 * @Version    		v0.1
 * @Date       		2020-1-8
 * @Target   		STM32F103C8T6
 * @company	   		HBUT - LanDian
 * @GitHub   		https://github.com/pomin-163
 ***************************************************/
#include "WS2812B.h"
#include "delay.h"

#define SIGNAL0_H_Time 400 // 0 码 高电平时间
#define SIGNAL0_L_Time 850 // 0 码 低电平时间
#define SIGNAL1_H_Time 850 // 1 码 高电平时间
#define SIGNAL1_L_Time 400 // 1 码 低电平时间

static void Signeal_0_H_Delay(void) {
    __nop();__nop();__nop();__nop();__nop();__nop();
}
static void Signeal_0_L_Delay(void) {
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}
static void Signeal_1_H_Delay(void) {
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}
static void Signeal_1_L_Delay(void) {
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}
static void WS2812B_Write0(void) {
	WS2812B_PIN_H;
    Signeal_0_H_Delay();
	WS2812B_PIN_L;
    Signeal_0_L_Delay();
}
static WS2812B_Write1(void) {
	WS2812B_PIN_H;
    Signeal_1_H_Delay();
	WS2812B_PIN_L;
    Signeal_1_L_Delay();
}



void WS2812B_Init(void) {
    GPIO_InitTypeDef  WS2810B;
    RCC_APB2PeriphClockCmd(WS2812B_CLK, ENABLE);

	WS2810B.GPIO_Pin = WS2812B_PIN;
	WS2810B.GPIO_Mode = GPIO_Mode_Out_PP;
	WS2810B.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(WS2810B_GPIO, &WS2810B);
}
void WS2812B_Reset(void) {
	WS2812B_PIN_L;
	delay_us(1000);
}
void WS2812B_Write_Byte(uint8_t byte) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		if (byte & 0x80) {
			WS2812B_Write1();
		}
		else {
			WS2812B_Write0();
		}
		byte <<= 1;
	}
}
void WS2812B_Write_24Bits(uint8_t red, uint8_t green, uint8_t blue) {
	WS2812B_Write_Byte(green);
	WS2812B_Write_Byte(red);
	WS2812B_Write_Byte(blue);
}
void WS2812B_All(uint8_t red, uint8_t green, uint8_t blue) {
	uint8_t i;
	for (i = 0; i < LED_NUM; i++) {
		WS2812B_Write_24Bits(red, green, blue);
	}
}
void WS2812B_Write_24Bits_RGB(RGB *color) {
	WS2812B_Write_Byte(color->G);
	WS2812B_Write_Byte(color->R);
	WS2812B_Write_Byte(color->B);
}
void WS2812B_All_RGB(RGB *color) {
	uint8_t i;
	for (i = 0; i < LED_NUM; i++) {
		WS2812B_Write_24Bits_RGB(color);
		delay_ms(100);
	}
}
