#include "led.h"

unsigned char LED_0F[] = {
// 0	 1  2	  3	4	 5	 6	 7	8	 9	  A	   b	C    d	  E    F    -
0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};
unsigned char SMG[4] = {0};
void LED_GPIO_Config(void) {
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);	
}
void SMG_GPIO_Config(void) {
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

void SMG_OUT(unsigned char X) {
	unsigned char i;
	for(i=8;i>=1;i--) {
		if (X & 0x80) {
				DIO = 1;
		}else {
				DIO = 0;
		}
		X <<= 1;
		SCLK = 0;
		SCLK = 1;
	}
}
void SMG_Display(unsigned int x) {
	unsigned char i;	
	for(i = 0; i < 4; i++){
     SMG[i] = x % 10;
		 x /= 10;
  }
	for(i = 0; i < 4; i++){
		SMG_OUT(LED_0F[SMG[i]]);
		SMG_OUT(0x01 << i);		
		RCLK = 0;
		RCLK = 1;
	}
}
