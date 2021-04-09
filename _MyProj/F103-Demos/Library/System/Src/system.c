#include "system.h"

void getRstStatus(void) {
    if (0 != (RCC->CSR & 0x80000000)) {  // 1.�͹��Ĺ���λ
        printDbg("1.Low-power reset");
    }
    if (0 != (RCC->CSR & 0x40000000)) {  // 2.���ڿ��Ź���λ
        printDbg("2.Window watchdog reset");
    }
    if (0 != (RCC->CSR & 0x20000000)) {  // 3.�������Ź���λ
        printDbg("3.(Independent watchdog reset");
    }
    if (0 != (RCC->CSR & 0x10000000)) {  // 4.�����λ
        printDbg("4.Software reset");
    }
    if (0 != (RCC->CSR & 0x08000000)) {  // 5.�ϵ�/���縴λ
        printDbg("5.POR/PDR reset");
    }
    if (0 != (RCC->CSR & 0x04000000)) {  // 6.PIN���Ÿ�λ
        printDbg("6.PIN reset");
    }
}
