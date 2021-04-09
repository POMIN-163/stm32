#include "system.h"

void getRstStatus(void) {
    if (0 != (RCC->CSR & 0x80000000)) {  // 1.低功耗管理复位
        printDbg("1.Low-power reset");
    }
    if (0 != (RCC->CSR & 0x40000000)) {  // 2.窗口看门狗复位
        printDbg("2.Window watchdog reset");
    }
    if (0 != (RCC->CSR & 0x20000000)) {  // 3.独立看门狗复位
        printDbg("3.(Independent watchdog reset");
    }
    if (0 != (RCC->CSR & 0x10000000)) {  // 4.软件复位
        printDbg("4.Software reset");
    }
    if (0 != (RCC->CSR & 0x08000000)) {  // 5.上电/掉电复位
        printDbg("5.POR/PDR reset");
    }
    if (0 != (RCC->CSR & 0x04000000)) {  // 6.PIN引脚复位
        printDbg("6.PIN reset");
    }
}
