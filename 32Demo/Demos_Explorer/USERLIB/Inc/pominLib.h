#ifndef __POMIN_LIB_H
#define __POMIN_LIB_H

// 一些宏
#ifndef true
    #define true 1
#endif
#ifndef false
    #define false 0
#endif
#define _NULL_ ((void *)0)
// 外设相关
#include "sys.h"
#include "systick.h"
#include "gpio.h"
#include "tim.h"
#include "nvic.h"
#include "exti.h"
#include "usart.h"
// 计算相关
#include "stdio.h"
#include "sort.h"
#include "fun.h"

#endif
