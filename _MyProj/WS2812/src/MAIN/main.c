/****************************************************
 * @Author     		POMIN
 * @Version    		v0.1
 * @Date       		2020-1-8
 * @Target   		STM32F103C8T6
 * @company	   		HBUT - LanDian
 * @GitHub   		https://github.com/pomin-163
 ***************************************************/
#include "delay.h"
#include "sys.h"
#include "WS2812B.h"

void LED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int main(void) {
	RGB rgb[LED_NUM];
	unsigned int i, j;
	delay_init();
	LED_Init();
	WS2812B_Init();
	while (1) {
		RGB R = {
			0,0,255,
		};
		RGB G = {
			0,255,0,
		};
		RGB B = {
			255,0,0,
		};
		for (i = 0; i <= LED_NUM; i++) {
			for (j = 0; j < i; j++) {
				WS2812B_Write_24Bits_RGB(&R);
			}
		    delay_ms(100);
		}
		PCout(13) = !PCout(13);
		delay_ms(500);
	}
}
