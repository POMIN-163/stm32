#include "Class_Sys.h"
#include "Class_GPIO.h"
#include "Class_USART.h"
#include "Led..Beep..Key.h"
#include "Class_EXTI.h"

Class_SYS sys;
Class_GPIO gpio;
Class_USART usart;
Class_EXTI exti;

void Init(void){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
    sys.Init(SysTick_CLKSource_HCLK_Div8, 168);// ϵͳ��ʱ
    gpio.Clock(RCC_AHB1Periph_GPIOA, ENABLE);// �˿�ʹ��
    usart.Clock(RCC_APB2Periph_USART1, ENABLE);// ����ʹ��
    usart.Config_AF(
        GPIOA
        ,GPIO_Pin_9
        ,GPIO_PinSource9
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
        ,GPIO_AF_USART1
    );// �˿ڸ��õ�����(Rx)
    usart.Config_AF(
        GPIOA
        ,GPIO_Pin_10
        ,GPIO_PinSource10
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
        ,GPIO_AF_USART1
    );// �˿ڸ��õ�����(Tx)
    usart.Config(
        USART1
        ,115200
        ,USART_WordLength_8b
        ,USART_StopBits_1
        ,USART_Parity_No
        ,USART_HardwareFlowControl_None
        ,USART_Mode_Rx | USART_Mode_Tx
    );// ���ô���
    usart.Cmd(USART1, ENABLE);// ʹ�ܴ���
    usart.Config_IT(USART1, USART_IT_RXNE, ENABLE);// ����ģʽ
    usart.Config_NVIC(USART1_IRQn, 3, 3, ENABLE);// �����ж�
    gpio.Clock(RCC_AHB1Periph_GPIOF, ENABLE);// LED
    gpio.Config(
         GPIOF
        ,GPIO_Pin_9|GPIO_Pin_10-
        ,GPIO_Mode_OUT
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
    );// LED
    gpio.Config(
         GPIOF
        ,GPIO_Pin_8
        ,GPIO_Mode_OUT
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_DOWN
    );// BEEP
    gpio.Clock(RCC_AHB1Periph_GPIOE, ENABLE);
    gpio.Config(
        GPIOE
        ,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4
        ,GPIO_Mode_IN
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
    );
    gpio.Clock(RCC_AHB1Periph_GPIOA, ENABLE);
    gpio.Config(
        GPIOA
        ,GPIO_Pin_1
        ,GPIO_Mode_IN
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_DOWN
    );// KEY
    exti.Clock(RCC_APB2Periph_SYSCFG, ENABLE);
    exti.Config_Line(EXTI_PortSourceGPIOE, EXTI_PinSource2);
    exti.Config_Line(EXTI_PortSourceGPIOE, EXTI_PinSource3);
    exti.Config_Line(EXTI_PortSourceGPIOE, EXTI_PinSource4);
    exti.Config_Line(EXTI_PortSourceGPIOA, EXTI_PinSource0);
    // �ж�������
    exti.Config(
        EXTI_Line0,
        EXTI_Mode_Interrupt,
        EXTI_Trigger_Rising,
        ENABLE
    );// �ж�1 (����)
    exti.Config(
      EXTI_Line2|EXTI_Line3|EXTI_Line4,
      EXTI_Mode_Interrupt,
      EXTI_Trigger_Falling,
      ENABLE
    );// �ж�2��3��4 (����)
    exti.Config_NVIC(EXTI0_IRQn, 0, 2, ENABLE);
    exti.Config_NVIC(EXTI2_IRQn, 3, 2, ENABLE);
    exti.Config_NVIC(EXTI3_IRQn, 2, 2, ENABLE);
    exti.Config_NVIC(EXTI4_IRQn, 1, 2, ENABLE);
    // NVIC���ȼ�
}

int main(void) {
    Init();
    while(1)
    {
      printf("OK\r\n");	//��ӡOK��ʾ��������
        sys.Delay_ms(500);
    }
}

