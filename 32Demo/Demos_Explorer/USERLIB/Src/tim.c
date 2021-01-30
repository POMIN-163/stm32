#include "tim.h"


void timBaseConf(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                 uint16_t TIM_CounterMode, uint16_t TIM_CKD
) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    switch ((uint32_t)TIMx)
    {
    case TIM1_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
        break;
    case TIM2_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
        break;
    case TIM3_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
        break;
    case TIM4_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
        break;
    case TIM5_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
        break;
    case TIM6_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
        break;
    case TIM7_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
        break;
    case TIM8_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
        break;
    case TIM9_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
        break;
    case TIM10_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
        break;
    case TIM11_BASE: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
        break;
    case TIM12_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
        break;
    case TIM13_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
        break;
    case TIM14_BASE: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
        break;
    default:
        break;
    }
    // ���û�����ʱ��
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD;
    TIM_TimeBaseInitStruct.TIM_Period = TIM_Period - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM_Prescaler - 1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);
    TIM_ITConfig(TIMx,TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}
void timPwmConf(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period,
                uint16_t TIM_CounterMode, uint16_t TIM_CKD, OC_TypeDef OCx,
                uint16_t TIM_OCMode, uint16_t TIM_OutputState, uint16_t TIM_OCPolarity
) {
    TIM_OCInitTypeDef TIM_OCInitStruct;
    // ���û�����ʱ��
    timBaseConf(TIMx,TIM_Prescaler,TIM_Period,TIM_CounterMode,TIM_CKD);
    // ���� PWM �����ͨ��
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity;
    switch (OCx)
    {
    case OC1: TIM_OC1Init(TIMx, &TIM_OCInitStruct); TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable); break;
    case OC2: TIM_OC2Init(TIMx, &TIM_OCInitStruct); TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable); break;
    case OC3: TIM_OC3Init(TIMx, &TIM_OCInitStruct); TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable); break;
    case OC4: TIM_OC4Init(TIMx, &TIM_OCInitStruct); TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable); break;
    default:
        break;
    }
    TIM_ARRPreloadConfig(TIMx,ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}

TIM_ICInitTypeDef  TIM5_ICInitStructure;

//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0����λ��ʱ��5


	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);


	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�

  TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5


  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����


}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ��5�жϷ������
void TIM5_IRQHandler(void)
{

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//���
		{
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½���
			{
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			  TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_Cmd(TIM5,DISABLE ); 	//�رն�ʱ��5
	 			TIM_SetCounter(TIM5,0);
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
				TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
			}
		}
 	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}



