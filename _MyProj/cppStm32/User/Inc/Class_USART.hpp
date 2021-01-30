#ifndef _ClASS_USART_H_
#define _ClASS_USART_H_
#include "usart.h"
#include "stm32f4xx.h"

class Class_USART{
   public:
/*
   gpio.Clock();// 端口使能
   usart.Clock();// 串口使能
   usart.Config_AF();// 端口复用到串口(Rx)
   usart.Config_AF();// 端口复用到串口(Tx)
   usart.Config();// 配置串口
	usart.Cmd();// 使能串口
	usart.Config_IT();// 设置模式
	usart.Config_NVIC();// 设置中断
 */
   void Tip(void);
/*
 * Set USART's setting
 * eg:
     USART
    ,115200
    ,USART_WordLength
    ,USART_StopBits
    ,USART_Parity
    ,USART_HardwareFlowControl
    ,USART_Mode_Rx | USART_Mode_Tx
 */
   void Config(
      USART_TypeDef* USARTx,
      uint32_t BaudRate,
      uint16_t WordLength,
      uint16_t StopBits,
      uint16_t Parity,
      uint16_t HardwareFlowControl,
      uint16_t Mode
   );
/*
 * Set USART's clock
 * eg: RCC_APB2Periph_USART1, ENABLE
 */
   void Clock(uint32_t RCC_APB2Periph, FunctionalState NewState);
/*
 * Set a GPIO's AF'setting or some GPIOs' AF'settings with "|"
 * eg:
     GPIO
    ,GPIO_Pin
    ,GPIO_PinSource
    ,GPIO_Speed
    ,GPIO_OType
    ,GPIO_PuPd
    ,GPIO_AF

   eg: GPIO, GPIO_Pin, GPIO_PinSource, GPIO_Speed, GPIO_OType, GPIO_PuPd, GPIO_AF
 */
   void Config_AF(
      GPIO_TypeDef* GPIOx,
      uint32_t GPIO_Pin,
      uint16_t GPIO_PinSource,
      GPIOSpeed_TypeDef GPIO_Speed,
      GPIOOType_TypeDef GPIO_OType,
      GPIOPuPd_TypeDef GPIO_PuPd,
      uint8_t GPIO_AF
   );
/*
 * Set USART's NVIC
 * eg:
     USART1_IRQn, 3, 3, ENABLE
 */
   void Config_NVIC(
      uint8_t NVIC_IRQChannel,
      uint8_t NVIC_IRQChannelPreemptionPriority,
      uint8_t NVIC_IRQChannelSubPriority,
      FunctionalState NVIC_IRQChannelCmd
   );
/*
 * Set USART's state
 * eg:
     USART1, ENABLE
     USART1, DISABLE
 */
   void Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/*
 * Set USART's IT state
 * eg:
     USART1, USART_IT_RXNE, ENABLE
 */
   void Config_IT(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
};

extern "C"{
   void _USART_Config(
      USART_TypeDef* USARTx,
      uint32_t BaudRate,
      uint16_t WordLength,
      uint16_t StopBits,
      uint16_t Parity,
      uint16_t HardwareFlowControl,
      uint16_t Mode
   );

   void _USART_Clock(uint32_t RCC_APB2Periph, FunctionalState NewState);

   void _USART_Config_AF(
      GPIO_TypeDef* GPIOx,
      uint32_t GPIO_Pin,
      uint16_t GPIO_PinSource,
      GPIOSpeed_TypeDef GPIO_Speed,
      GPIOOType_TypeDef GPIO_OType,
      GPIOPuPd_TypeDef GPIO_PuPd,
      uint8_t GPIO_AF
   );

   void _USART_Config_NVIC(
      uint8_t NVIC_IRQChannel,
      uint8_t NVIC_IRQChannelPreemptionPriority,
      uint8_t NVIC_IRQChannelSubPriority,
      FunctionalState NVIC_IRQChannelCmd
   );

   void _USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);

   void _USART_Config_IT(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
}

#endif
