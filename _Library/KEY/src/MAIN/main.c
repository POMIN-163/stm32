#include "led.h"
#include "key.h"
#include "beep.h"
#include "delay.h"

int main(void){
	u8 key_Value;
	delay_init(168);		  //初始化延时函数
	led_Init();
	beep_Init();
	key_Init();
	while(1){
		key_Value = key_Scan(0);
		if(key_Value)// 为0直接跳过,提高效率
		{
			switch (key_Value)
			{
				case 1:
					led1 = !led1;
					break;
				case 2:
					led2 = !led2;
					break;
				case 3:
					led2 = !led2;
					led1 = !led1;
					break;
				case 4:
					BEEP = !BEEP;
					break;
				default:
					break;
			}
		}else
		{
			delay_ms(20);
		}
	}
}
