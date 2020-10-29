#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "tim.h"

int main(void)
{	u16 num = 0;
	delay_init();	    //延时函数初始化	  

	LED_GPIO_Config();
	SMG_GPIO_Config();
  //TIM3_Int_Init(2,7200);
	while(1)
	{
    SMG_Display(7850);
	}
}
