#include "delay.h"
#include "ec11.h"
#include "led.h"
#include "sys.h"
int main(void) {
    uint8_t msg;
    delay_init();
    LED_Init();
    ec11Init();
    while (1) {
        ec11Scan(&msg);
    }
}
