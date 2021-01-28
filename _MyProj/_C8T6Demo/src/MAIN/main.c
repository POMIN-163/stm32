#include "delay.h"
#include "led.h"
#include "key.h"

void Demo_LED(void) {
	LED_Init();
	while(1){
		delay_init();
		LED_Toggle();
		delay_ms(500);
	}
}
void Demo_KEY(void) {
	u16 KeyValue = 0;
	u8 i;
	LED_Init();
	KEY_Init();
	while (1) {
		keyScan(&KeyValue);
		if(KeyValue > 0) {
			for ( i = 0; i < KeyValue; i++) {
				LED_Toggle();
				delay_ms(500);
				LED_Toggle();
				delay_ms(500);
			}
		}
	}
}
int main(void) {
	delay_init();
	// Demo_LED();
	Demo_KEY();
}

