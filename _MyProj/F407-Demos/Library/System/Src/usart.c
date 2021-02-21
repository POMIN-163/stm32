#include "usart.h"
/**
 * @brief 串口配置函数
 *
 * @param USARTx                    串口号
 * @param USART_BaudRate            波特率
 * @param USART_WordLength          数据字长
 * @param USART_StopBits            停止位
 * @param USART_Parity              奇偶校验
 * @param USART_Mode                收发模式
 * @param USART_HardwareFlowControl 硬件流控制
**/
void uartConf(USART_TypeDef *USARTx, uint32_t USART_BaudRate, uint16_t USART_WordLength,
              uint16_t USART_StopBits, uint16_t USART_Parity,
              uint16_t USART_Mode, uint16_t USART_HardwareFlowControl
) {
    USART_InitTypeDef USART_InitStructure;
    switch ((int32_t)USARTx)
    {
    case USART1_BASE:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        break;
    case USART2_BASE:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        break;
    case USART3_BASE:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        break;
    case USART6_BASE:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
        break;
    default:
        break;
    }
    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength;
    USART_InitStructure.USART_StopBits = USART_StopBits;
    USART_InitStructure.USART_Parity = USART_Parity;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl;
    USART_InitStructure.USART_Mode = USART_Mode;
    USART_Init(USARTx, &USART_InitStructure);
    USART_Cmd(USARTx, ENABLE);
    if((USART_Mode & USART_Mode_Rx) != 0) {
        USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
    }
}
