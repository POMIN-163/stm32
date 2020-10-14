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
        Temp.USART_BaudRate = BaudRate;//波特率设置
        Temp.USART_WordLength = WordLength;//字长为8位数据格式
        Temp.USART_StopBits = StopBits;//一个停止位
        Temp.USART_Parity = Parity;//无奇偶校验位
        Temp.USART_HardwareFlowControl = HardwareFlowControl;//无硬件数据流控制
        Temp.USART_Mode = Mode;	//收发模式
    USART_Init(USARTx, &Temp); //初始化串口
}

void Class_USART::Config_IT(
    USART_TypeDef* USARTx,
    uint16_t USART_IT,
    FunctionalState NewState
){
    USART_ITConfig(USARTx, USART_IT, NewState);//开启相关中断
}

void Class_USART::Cmd(USART_TypeDef* USARTx, FunctionalState NewState){
    USART_Cmd(USARTx, NewState);
}

void Class_USART::Clock(uint32_t RCC_APB2Periph, FunctionalState NewState){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, NewState);//使能USART1时钟
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
        Temp.USART_BaudRate = BaudRate;//波特率设置
        Temp.USART_WordLength = WordLength;//字长为8位数据格式
        Temp.USART_StopBits = StopBits;//一个停止位
        Temp.USART_Parity = Parity;//无奇偶校验位
        Temp.USART_HardwareFlowControl = HardwareFlowControl;//无硬件数据流控制
        Temp.USART_Mode = Mode;	//收发模式
    USART_Init(USARTx, &Temp); //初始化串口
}

void _USART_Config_IT(
    USART_TypeDef* USARTx,
    uint16_t USART_IT,
    FunctionalState NewState
){
    USART_ITConfig(USARTx, USART_IT, NewState);//开启相关中断
}

void _USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState){
    USART_Cmd(USARTx, NewState);
}

void _USART_Clock(uint32_t RCC_APB2Periph, FunctionalState NewState){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, NewState);//使能USART1时钟
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


