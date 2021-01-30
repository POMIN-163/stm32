#include "delay.h"
#include "sys.h"
#include "led.h"

int main(void)
{
  LED_Init();
	while(1){
		delay_init();
		PBout(5) = !PBout(5);
		delay_ms(500);
	}
}

