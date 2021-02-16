#ifndef __SYSTEM_H
#define __SYSTEM_H

// 外设相关
#include "systick.h"
#include "gpio.h"
#include "tim.h"
#include "nvic.h"
#include "exti.h"
#include "usart.h"
// 位带操作
// 公式：最终地址 ＝ 0x42000000 + ((A ‐ 0x40000000)*8 + n)*4 = 0x42000000 + (A ‐ 0x40000000)*32 + n*4
// 解释：别名区基址：0x42000000  *8 bit 膨胀到 Byte  +n 找到管脚的某位
//      寄存器基址：0x40000000

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
#define PHout(n) BIT_REG (GPIOH->ODR, n)
#define PIout(n) BIT_REG (GPIOI->ODR, n)

#define PAin(n) BIT_REG (GPIOA->IDR, n)
#define PBin(n) BIT_REG (GPIOB->IDR, n)
#define PCin(n) BIT_REG (GPIOC->IDR, n)
#define PDin(n) BIT_REG (GPIOD->IDR, n)
#define PEin(n) BIT_REG (GPIOE->IDR, n)
#define PFin(n) BIT_REG (GPIOF->IDR, n)
#define PGin(n) BIT_REG (GPIOG->IDR, n)
#define PHin(n) BIT_REG (GPIOH->IDR, n)
#define PIin(n) BIT_REG (GPIOI->IDR, n)

#endif
