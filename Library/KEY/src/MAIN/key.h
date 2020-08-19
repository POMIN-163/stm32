#ifndef _KEY_H_
#define _KEY_H_
#include "sys.h"
#include "delay.h"

#if 1
    #define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
    #define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
    #define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
    #define WK_UP GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#else
    #define KEY0 PEin(4)
    #define KEY1 PEin(3)
    #define KEY2 PEin(2)
    #define WK_UP PEin(0)
#endif

void key_Init(void);
u8 key_Scan(u8 mode);

#endif
