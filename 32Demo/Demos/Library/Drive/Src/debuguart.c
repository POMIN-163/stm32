#include "debuguart.h"

#define DEBUG_UART USART1
#define DEBUG_PORT GPIOA
#define DEBUG_T GPIO_Pin_9
#define DEBUG_R GPIO_Pin_10

uint8_t debugRxFlag = 0;            // 接收标志位 (0: 正常接收消息, 1: 等待被清零 (消息作废))
uint8_t recLength = 0;              // 接收长度
uint8_t debugRxBuff[DEBUG_MAX_LEN]; // 缓冲区
void (*debugFun)(void);             // 调试串口响应函数
/**
 * @brief 调试串口重定义到 printf
 *
**/
#pragma import(__use_no_semihosting)
struct __FILE {
    int handle;
};
FILE __stdout;
void _sys_exit(int x) {
    x = x;
}
int fputc(int ch, FILE *f) {                // 重定义 fputc 函数
    while ((DEBUG_UART -> SR & 0X40) == 0); // 发送数据帧
    DEBUG_UART -> DR = (u8)ch;
    return ch;
}
/**
 * @brief 初始化调试串口
 *
 * @param baud 波特率
**/
void debugInit(uint32_t baud) {
    gpioAFConf(DEBUG_PORT, DEBUG_T | DEBUG_R, GPIO_Fast_Speed, GPIO_OType_PP,
               GPIO_PuPd_UP, GPIO_AF_USART1);
#ifdef EN_DEBUG_RX
    uartConf(DEBUG_UART, baud, USART_WordLength_8b, USART_StopBits_1,
             USART_Parity_No, USART_Mode_RxTx, USART_HardwareFlowControl_None);
#else
    uartConf(DEBUG_UART, baud, USART_WordLength_8b, USART_StopBits_1,
             USART_Parity_No, USART_Mode_Tx, USART_HardwareFlowControl_None);
#endif
    nvicIRQConf(USART1_IRQn, 3, 3);
}
/**
 * @brief 清除调试串口 Flag 并且执行响应函数
 *
**/
void debugReply(void) {
    if(debugRxFlag != 0) {
        if(debugFun != _NULL_) {
            debugFun();
            debugRxFlag = 0;
        }
    }
}
/**
 * @brief 调试串口接收中断 (串口是数据帧接收)
 *
**/
void USART1_IRQHandler(void) {
    uint8_t Rec;
    if (USART_GetITStatus(DEBUG_UART, USART_IT_RXNE) != RESET) {
        Rec = USART_ReceiveData(DEBUG_UART);
        if(debugRxFlag == 0) {                                         // 仅当响应完成才可接收
            if (Rec == '\n' && (debugRxBuff[recLength - 1] == '\r')) { // 接收完成
                debugRxBuff[recLength] = '\0';
                recLength = 0;
                debugRxFlag = 1;
                print("RECEIVE");
            } else {
                debugRxBuff[recLength++] = Rec;                         // 接收到一帧
            }
        } else {
            print("ERROR\r\n");
        }
    }
}

/**
 * @brief print 变参函数, 功能有限, 不支持float
 *
 * @param fmt 字符串
 * @param ... 可变参数
**/
typedef char *va_list;

#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int*) - 1) & ~(sizeof(int*) - 1))
#define va_start_(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))
#define va_arg_(ap, t) (*(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))
#define va_end_(ap) (ap = (va_list)0)

void putch(uint8_t ch) {
    PRINT_USART->DR = ch;
    while((PRINT_USART->SR & 0X40) == 0);
}
void putstr(uint8_t *str) {
    while(*str != '\0') {
        putch(*str);
        str++;
    }
}
void putnum(int32_t num, uint8_t carry) {
    int8_t num_arr[10];
    uint8_t i;
    if (num < 0) {
        putch('-');
        num = -num;
    }
    for (i = 0; i < 10; i++) {
        if (!num) break;
        num_arr[i] = num % carry;
        num /= carry;
    }
    while(i--) {
        putch(num_arr[i] + 48);
    }
}
void print(const char *fmt, ...) {
    va_list ap;
    va_start_(ap, fmt);
    while((PRINT_USART -> SR & 0X40) == 0);
    for (; *fmt != '\0'; fmt++) {
        if (*fmt != '%') {
            putch(*fmt);
            continue;
        }
        fmt++;
        switch (*fmt) {
            case 'd':
                putnum(va_arg_(ap, int), 10);
                break;
            case 'x':
                putnum(va_arg_(ap, int), 16);
                break;
            case 'o':
                putnum(va_arg_(ap, int), 8);
                break;
            case 'c':
                putch(va_arg_(ap, char));
                break;
            case 's':
                putstr((uint8_t *) va_arg_(ap, char*));
                break;
            default:
                putch(*fmt);
                break;
        }
    }
    va_end_(ap);
}

