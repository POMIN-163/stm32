#include "debuguart.h"

#define DEBUG_UART USART1
#define DEBUG_PORT GPIOA
#define DEBUG_T GPIO_Pin_9
#define DEBUG_R GPIO_Pin_10

uint8_t debugRxFlag = 0;            // ���ձ�־λ (0: ����������Ϣ, 1: �ȴ������� (��Ϣ����))
uint8_t recLength = 0;              // ���ճ���
int8_t debugRxBuff[DEBUG_MAX_LEN];  // ������
Func debugFun;                      // ���Դ�����Ӧ����

/**
 * @brief ���Դ����ض��嵽 printf
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
int fputc(int ch, FILE *f) {                // �ض��� fputc ����
    while ((DEBUG_UART -> SR & 0X40) == 0); // ��������֡
    DEBUG_UART -> DR = (u8)ch;
    return ch;
}
/**
 * @brief ��ʼ�����Դ���
 *
 * @param baud ������
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
 * @brief ������Դ��� Flag ����ִ����Ӧ���� (��ʹ��shellʱ)
 *
**/
void debugReply(void) {
    if(debugRxFlag != 0) {
        if(debugFun != _NULL_) {
            debugFun();
            debugRxFlag = 0;
        } else {
            printf("%s\r\n", debugRxBuff);
        }
    }
}
/**
 * @brief ���Դ��ڽ����ж� (����������֡����)
 *
**/
void USART1_IRQHandler(void) {
    uint8_t Rec;
    if (USART_GetITStatus(DEBUG_UART, USART_IT_RXNE) != RESET) {
        Rec = USART_ReceiveData(DEBUG_UART);
        #if 1 == USE_SHELL
        shellHandler(&shell, Rec);
        #else
        if(debugRxFlag == 0) {                                         // ������Ӧ��ɲſɽ���
            if (Rec == '\n' && (debugRxBuff[recLength - 1] == '\r')) { // �������
                debugRxBuff[recLength] = '\0';
                recLength = 0;
                debugRxFlag = 1;

                print("RECEIVE\n");
            } else {
                debugRxBuff[recLength++] = Rec;                         // ���յ�һ֡
            }
        } else {
            print("ERROR\n");
        }
        #endif
    }
}
#if 1
/**
 * @brief print ��κ���, ��������, ��֧��float
 *
 * @param fmt �ַ���
 * @param ... �ɱ����
**/
typedef char *va_list_;

#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int*) - 1) & ~(sizeof(int*) - 1))
#define va_start_(ap, v) (ap = (va_list_)&v + _INTSIZEOF(v))
#define va_arg_(ap, t) (*(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))
#define va_end_(ap) (ap = (va_list_)0)

void putch(const char ch) {
    PRINT_USART->DR = ch;
    while((PRINT_USART->SR & 0X40) == 0);
}
void putstr(uint8_t *str) {
    while(*str != '\0') {
        putch(*str);
        str++;
    }
}
uint8_t char_0_F[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
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
        putch(char_0_F[num_arr[i]]);
    }
}
void print(const char *fmt, ...) {
    va_list_ ap;
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
                putnum(va_arg_(ap, int), 10); // ʮ����
                break;
            case 'x':
                putnum(va_arg_(ap, int), 16); // ʮ������
                break;
            case 'o':
                putnum(va_arg_(ap, int), 8);  // �˽���
                break;
            case 'c':
                putch(va_arg_(ap, char));     // �ַ�
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

#endif