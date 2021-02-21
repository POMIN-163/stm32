#ifndef __DEBUGUART_H
#define __DEBUGUART_H
#include "system.h"

#define DEBUG_MAX_LEN  500      // 定义最大接收字节数
#define EN_DEBUG_RX    1        // 使能调试串口接收

extern int8_t debugRxBuff[DEBUG_MAX_LEN];  // 接收缓冲, 末字节为换行符
extern uint8_t debugRxStatus;              // 接收状态标记
extern void (*debugFun)(void);             // 调试串口响应函数

void debugInit(uint32_t baud);      // 调试串口初始化
void debugReply(void);              // 调试串口响应

#define PRINT_USART USART1          // 由于 printf 绑定在了调试串口,
void putch(int8_t ch);
void putnum(int32_t num, uint8_t carry);
void putstr(uint8_t *str);          // 发送字符串
void print(const char *fmt, ...);   // 此函数可以换到其他串口进行多串口调试

#endif
