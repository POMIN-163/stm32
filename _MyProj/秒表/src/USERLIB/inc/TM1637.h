#ifndef   __TM1637_H
#define   __TM1637_H
#include "stm32f10x.h"

//与库函数操作取一个
#define    SDA_IN()  {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=(u32)8<<28;}      //通过寄存器更改为输入
#define    SDA_OUT() {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=(u32)3<<28;}      //通过寄存器更改为输出

#define    TM_SCL_PORT        GPIOA
#define    TM_SCL_CLK         RCC_APB2Periph_GPIOA
#define    TM_SCL_PIN         GPIO_Pin_8

#define    TM_DIO_PORT        GPIOA
#define    TM_DIO_CLK         RCC_APB2Periph_GPIOA
#define    TM_DIO_PIN         GPIO_Pin_9

#define TM_SCL PAout(8)
#define TM_SDA PAout(9)
void TM_Init(void);
void TM_Display(uint8_t *discode);

#endif
