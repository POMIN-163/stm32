#ifndef _LED_BEEP_KEY_H_
#define _LED_BEEP_KEY_H_
#include "stm32f4xx.h"

// �Ƿ����ú궨��
#if 1
#include "sys.h"
    // LED
    #define LED1 PFout(9)
    #define LED2 PFout(10)
    // BEEP
    #define BEEP PFout(8)
    // KEY
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
#endif

/*
 * mode: ����Ϊ 0 ʱ��֧������, ���� 0 ʱ֧������
 * delay: �������� ms
 */
u8 key_Scan(u8 mode, u8 delay);

#endif
