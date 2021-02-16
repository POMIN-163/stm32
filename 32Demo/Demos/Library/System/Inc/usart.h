#ifndef __USART_H
#define __USART_H
#include "stm32f4xx.h"

void uartConf(USART_TypeDef *USARTx, uint32_t USART_BaudRate,
              uint16_t USART_WordLength, uint16_t USART_StopBits,
              uint16_t USART_Parity, uint16_t USART_Mode,
              uint16_t USART_HardwareFlowControl
);

#endif


