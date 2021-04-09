/****************************************************
 * @Author     		POMIN
 * @Version    		v0.1
 * @Date       		2020-1-8
 * @Target   		STM32F103C8T6
 * @company	   		HBUT - LanDian
 * @GitHub   		https://github.com/pomin-163
 ***************************************************/
#include "WS2812B.h"

#define SIGNAL0_H_Time 400 // 0 码 高电平时间
#define SIGNAL0_L_Time 850 // 0 码 低电平时间
#define SIGNAL1_H_Time 850 // 1 码 高电平时间
#define SIGNAL1_L_Time 400 // 1 码 低电平时间

static void rgbWrite0(void) {
    WS2812B = 1;
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    WS2812B = 0;
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
}
static void rgbWrite1(void) {
    WS2812B = 1;
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    WS2812B = 0;
    __nop();__nop();__nop();
}
void rgbInit(void) {
    gpioConf(WS2812B_IO, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
}
void rgbWrite_Byte(uint8_t byte) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		if (byte & 0x80) {
			rgbWrite1();
		}
		else {
			rgbWrite0();
		}
		byte <<= 1;
	}
}
void rgbWrite_One(uint8_t red, uint8_t green, uint8_t blue) {
	rgbWrite_Byte(green);
	rgbWrite_Byte(red);
	rgbWrite_Byte(blue);
}
void rgbAll(uint8_t red, uint8_t green, uint8_t blue) {
	uint8_t i;
	for (i = 0; i < RGB_NUM; i++) {
		rgbWrite_One(red, green, blue);
	}
}

