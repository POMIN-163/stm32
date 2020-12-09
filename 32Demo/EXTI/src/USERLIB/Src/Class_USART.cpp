#include "Class_USART.h"

void Class_USART::Config(
            USART_TypeDef* USARTx,
            uint32_t BaudRate,
            uint16_t WordLength,
            uint16_t StopBits,
            uint16_t Parity,
            uint16_t HardwareFlowControl,
            uint16_t Mode
){
    USART_InitTypeDef Temp;
        Temp.USART_BaudRate = BaudRate;//����������
        Temp.USART_WordLength = WordLength;//�ֳ�Ϊ8λ���ݸ�ʽ
        Temp.USART_StopBits = StopBits;//һ��ֹͣλ
        Temp.USART_Parity = Parity;//����żУ��λ
        Temp.USART_HardwareFlowControl = HardwareFlowControl;//��Ӳ������������
        Temp.USART_Mode = Mode;	//�շ�ģʽ
    USART_Init(USARTx, &Temp); //��ʼ������
}

void Class_USART::Config_IT(
    USART_TypeDef* USARTx,
    uint16_t USART_IT,
    FunctionalState NewState
){
    USART_ITConfig(USARTx, USART_IT, NewState);//��������ж�
}

void Class_USART::Cmd(USART_TypeDef* USARTx, FunctionalState NewState){
    USART_Cmd(USARTx, NewState);
}

void Class_USART::Clock(uint32_t RCC_APB2Periph, FunctionalState NewState){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, NewState);//ʹ��USART1ʱ��
}

void Class_USART::Config_AF(
    GPIO_TypeDef* GPIOx,
    uint32_t GPIO_Pin,
    uint16_t GPIO_PinSource,
    GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType,
    GPIOPuPd_TypeDef GPIO_PuPd,
    uint8_t GPIO_AF
) {
    GPIO_PinAFConfig(GPIOx,GPIO_PinSource,GPIO_AF);
    GPIO_InitTypeDef Temp={GPIO_Pin, GPIO_Mode_AF, GPIO_Speed, GPIO_OType, GPIO_PuPd};
    GPIO_Init(GPIOx, &Temp);
}

void Class_USART::Config_NVIC(
    uint8_t IRQChannel,
    uint8_t IRQChannelPreemptionPriority,
    uint8_t IRQChannelSubPriority,
    FunctionalState IRQChannelCmd
){
    NVIC_InitTypeDef Temp;
    Temp.NVIC_IRQChannel = IRQChannel;
    Temp.NVIC_IRQChannelPreemptionPriority = IRQChannelPreemptionPriority;
    Temp.NVIC_IRQChannelSubPriority = IRQChannelSubPriority;
    Temp.NVIC_IRQChannelCmd = IRQChannelCmd;
    NVIC_Init(&Temp);
}

void Class_USART::Tip(void){
    while (1);
}

/////////////////////////////////////////////////////////////////////////

void _USART_Config(
            USART_TypeDef* USARTx,
            uint32_t BaudRate,
            uint16_t WordLength,
            uint16_t StopBits,
            uint16_t Parity,
            uint16_t HardwareFlowControl,
            uint16_t Mode
){
    USART_InitTypeDef Temp;
        Temp.USART_BaudRate = BaudRate;//����������
        Temp.USART_WordLength = WordLength;//�ֳ�Ϊ8λ���ݸ�ʽ
        Temp.USART_StopBits = StopBits;//һ��ֹͣλ
        Temp.USART_Parity = Parity;//����żУ��λ
        Temp.USART_HardwareFlowControl = HardwareFlowControl;//��Ӳ������������
        Temp.USART_Mode = Mode;	//�շ�ģʽ
    USART_Init(USARTx, &Temp); //��ʼ������
}

void _USART_Config_IT(
    USART_TypeDef* USARTx,
    uint16_t USART_IT,
    FunctionalState NewState
){
    USART_ITConfig(USARTx, USART_IT, NewState);//��������ж�
}

void _USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState){
    USART_Cmd(USARTx, NewState);
}

void _USART_Clock(uint32_t RCC_APB2Periph, FunctionalState NewState){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, NewState);//ʹ��USART1ʱ��
}

void _USART_Config_AF(
    GPIO_TypeDef* GPIOx,
    uint32_t GPIO_Pin,
    uint16_t GPIO_PinSource,
    GPIOSpeed_TypeDef GPIO_Speed,
    GPIOOType_TypeDef GPIO_OType,
    GPIOPuPd_TypeDef GPIO_PuPd,
    uint8_t GPIO_AF
) {
    GPIO_PinAFConfig(GPIOx,GPIO_PinSource,GPIO_AF);
    GPIO_InitTypeDef Temp={GPIO_Pin, GPIO_Mode_AF, GPIO_Speed, GPIO_OType, GPIO_PuPd};
    GPIO_Init(GPIOx, &Temp);
}

void _USART_Config_NVIC(
    uint8_t IRQChannel,
    uint8_t IRQChannelPreemptionPriority,
    uint8_t IRQChannelSubPriority,
    FunctionalState IRQChannelCmd
){
    NVIC_InitTypeDef Temp;
    Temp.NVIC_IRQChannel = IRQChannel;
    Temp.NVIC_IRQChannelPreemptionPriority = IRQChannelPreemptionPriority;
    Temp.NVIC_IRQChannelSubPriority = IRQChannelSubPriority;
    Temp.NVIC_IRQChannelCmd = IRQChannelCmd;
    NVIC_Init(&Temp);
}


