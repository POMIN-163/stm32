#include "exti.h"
#include "Led..Beep..Key.h"

//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	_SYS_Delay_ms(20);
	if(WK_UP==1)
	{
		BEEP=!BEEP; //��������ת
	}
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ
}
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	_SYS_Delay_ms(20);	//����
	if(KEY2==0)
	{
   LED1=!LED1;
	}
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	_SYS_Delay_ms(20);	//����
	if(KEY1==0)
	{
		LED2=!LED2;
	}
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	_SYS_Delay_ms(10);	//����
	if(KEY0==0)
	{
		LED1=!LED1;
		LED2=!LED2;
	}
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ
}




