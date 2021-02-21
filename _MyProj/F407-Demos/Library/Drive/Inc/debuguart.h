#ifndef __DEBUGUART_H
#define __DEBUGUART_H
#include "system.h"

#define DEBUG_MAX_LEN  500      // �����������ֽ���
#define EN_DEBUG_RX    1        // ʹ�ܵ��Դ��ڽ���

extern int8_t debugRxBuff[DEBUG_MAX_LEN];  // ���ջ���, ĩ�ֽ�Ϊ���з�
extern uint8_t debugRxStatus;              // ����״̬���
extern void (*debugFun)(void);             // ���Դ�����Ӧ����

void debugInit(uint32_t baud);      // ���Դ��ڳ�ʼ��
void debugReply(void);              // ���Դ�����Ӧ

#define PRINT_USART USART1          // ���� printf �����˵��Դ���,
void putch(int8_t ch);
void putnum(int32_t num, uint8_t carry);
void putstr(uint8_t *str);          // �����ַ���
void print(const char *fmt, ...);   // �˺������Ի����������ڽ��жമ�ڵ���

#endif
