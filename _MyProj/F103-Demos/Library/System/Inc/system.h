#ifndef __SYSTEM_H
#define __SYSTEM_H

// �������
#include "systick.h"
#include "gpio.h"
#include "tim.h"
#include "nvic.h"
#include "exti.h"
#include "usart.h"

// һЩ��Դ��
#if 1 == USE_SHELL
    #include "shell.h"
    extern Shell shell;
    extern int8_t  _int8_;
    extern int16_t _int16_;
    extern int32_t _int32_;
    extern int32_t *_point_;
#endif
#if 1 == USE_ELOG
    #include "elog.h"
#endif

// λ������
// ��ʽ�����յ�ַ �� 0x42000000 + ((A �\ 0x40000000)*8 + n)*4 = 0x42000000 + (A �\ 0x40000000)*32 + n*4
// ���ͣ���������ַ��0x42000000  *8 bit ���͵� Byte  +n �ҵ��ܽŵ�ĳλ
//      �Ĵ�����ַ��0x40000000

#define BIT_REG(Reg, Bit) (*((uint32_t volatile*)                     \
    (0x42000000u + (((uint32_t) & (Reg) - (uint32_t)0x40000000u) << 5) +  \
    (((uint32_t)(Bit)) << 2))))

#define PAout(n) BIT_REG (GPIOA->ODR, n)
#define PBout(n) BIT_REG (GPIOB->ODR, n)
#define PCout(n) BIT_REG (GPIOC->ODR, n)
#define PDout(n) BIT_REG (GPIOD->ODR, n)
#define PEout(n) BIT_REG (GPIOE->ODR, n)
#define PFout(n) BIT_REG (GPIOF->ODR, n)
#define PGout(n) BIT_REG (GPIOG->ODR, n)

#define PAin(n) BIT_REG (GPIOA->IDR, n)
#define PBin(n) BIT_REG (GPIOB->IDR, n)
#define PCin(n) BIT_REG (GPIOC->IDR, n)
#define PDin(n) BIT_REG (GPIOD->IDR, n)
#define PEin(n) BIT_REG (GPIOE->IDR, n)
#define PFin(n) BIT_REG (GPIOF->IDR, n)
#define PGin(n) BIT_REG (GPIOG->IDR, n)

#endif