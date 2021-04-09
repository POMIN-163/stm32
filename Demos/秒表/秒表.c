#include "stm32f10x.h"
#include "system.h"
#include "delay.h"
#include "GPIO.h"
#include "TM1637.h"
/*
*������PA1��   2��    3
*     ������ ��ͣ�� ����
*����ܣ�PA8�� 9
*       DIO�� CLK
*/
u8 G_status = 0;
// 1: ����, 2: ��ͣ, 3: ����
u8 G_time[2] = {0, 0,};
// �롢10ms
u8 time[4] = {0x3f, 0x3f, 0x3f, 0x4f,};

unsigned const char LED_0_9[10]={
    // 0:	1	 2:	  3	  4:	5   6:	 7	 8:	  9
    0xbf,0x06,0xdb,0x4f,0xe6,0x6d,0xfd,0x07,0xff,0x6f};

void TIM3_Init(u16 arr,u16 psc);// ��ʱ��
void TIM2_Init(u16 arr,u16 psc);// ˢ����
void Init(void);
void Transfrom(void);
u8 Keyscan(void);

void TIM3_Init(u16 arr,u16 psc) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx
}
void TIM2_Init(u16 arr,u16 psc) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);
}
void Init(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
// ��
    _GPIO_Config(
        GPIOC,
        GPIO_Pin_13,
        GPIO_Mode_Out_PP, GPIO_Speed_50MHz
    );
// ����
    _GPIO_Config(
        GPIOA,
        GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
        GPIO_Mode_IPU, GPIO_Speed_50MHz
    );
// �����
    _GPIO_Config(
        GPIOA,
        GPIO_Pin_8 | GPIO_Pin_9,
        GPIO_Mode_Out_PP, GPIO_Speed_50MHz
    );
    delay_init();
    TIM2_Init(10, 720);// 100us
    TIM3_Init(100, 7200);// 10ms
    TM_Init();
}
u8 Keyscan(void){
    // ����
    if(!PAin(3)){
        while(!PAin(3));
        return 3;
    // ��ͣ
    }if(!PAin(2)){
        while(!PAin(2));
        return 2;
    // ����
    }if(!PAin(1)){
        while(!PAin(1));
        return 1;
    } return 0;
}

//��ʱ��3�ж�, ��ʱ��
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        // ����
        switch(G_status){
        case 1:
            if(G_time[0] == 99 && G_time[1] == 99){
            }
            else {
                G_time[0]++;
                if(G_time[0] == 100) {
                    G_time[0] = 0;
                    G_time[1]++;
                    PCout(13) = ! PCout(13);
                }
            }
            break;
        // ��ͣ
        case 2:
            break;
        // ����
        case 3:
            G_time[0] = G_time[1] = 0;
            G_status = 0;
            break;
        }
    	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־
	}
}

// ��ʱ��2�ж�, �����ˢ��
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        Transfrom();
        TM_Display(time);
    	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx�����жϱ�־
	}
}
// ��λ(�롢10ms)ת����λ�ַ�
void Transfrom(void){
    time[3] = LED_0_9[G_time[0] % 10];
    time[2] = LED_0_9[G_time[0] / 10];
    time[1] = LED_0_9[G_time[1] % 10];
    time[0] = LED_0_9[G_time[1] / 10];
}
int main(void) {
    u8 temp;
    Init();// �����ܽų�ʼ��
    while(1) {
        temp = Keyscan();
        if(G_status == 2 && temp == 2) G_status = temp = 1;// ��ͣ����������
        if(temp) G_status = temp;
    }
}



