#include "beep.h"

void beepInit(void) {
    GPIO_InitTypeDef BEEP_Init_Struct;
    BEEP_Init_Struct.Pin = BEEP_PIN;
    BEEP_Init_Struct.Pull = GPIO_PULLUP;
    BEEP_Init_Struct.Speed = GPIO_SPEED_HIGH;
    BEEP_Init_Struct.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(BEEP_PORT, &BEEP_Init_Struct);
}
void beepOn(void) {
    HAL_GPIO_WritePin(BEEP_IO, GPIO_PIN_SET);
}
void beepOff(void) {
    HAL_GPIO_WritePin(BEEP_IO, GPIO_PIN_RESET);
}
