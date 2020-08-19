#include "stm32f4xx.h"
#include "beep.h"
#include "delay.h"
int main(void){
	while(1){
		delay_init(168);		  //初始化延时函数
		beep_Init();
		#if 0
			GPIO_ResetBits(GPIOF, GPIO_Pin_8);
			delay_ms(300);
			GPIO_SetBits(GPIOF, GPIO_Pin_8);
			delay_ms(300);
		#elif 0
			PFout(8) = 0;
			delay_ms(300);
			PFout(8) = 1;
			delay_ms(300);
		#else
			BEEP = 0;
			delay_ms(300);
			BEEP = 1;
			delay_ms(300);
		#endif
	}
}
