#include "exti.h"
#include "Led..Beep..Key.h"

//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	_SYS_Delay_ms(20);
	if(WK_UP==1)
	{
		BEEP=!BEEP; //蜂鸣器翻转
	}
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位
}
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	_SYS_Delay_ms(20);	//消抖
	if(KEY2==0)
	{
   LED1=!LED1;
	}
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	_SYS_Delay_ms(20);	//消抖
	if(KEY1==0)
	{
		LED2=!LED2;
	}
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	_SYS_Delay_ms(10);	//消抖
	if(KEY0==0)
	{
		LED1=!LED1;
		LED2=!LED2;
	}
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位
}




