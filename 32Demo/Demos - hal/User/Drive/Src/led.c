#include "led.h"

void ledInit(void) {
    GPIO_InitTypeDef LED_Init_Struct;
    __HAL_RCC_GPIOF_CLK_ENABLE();
    LED_Init_Struct.Pin = LED_PIN;
    LED_Init_Struct.Pull = GPIO_PULLUP;
    LED_Init_Struct.Mode = GPIO_MODE_OUTPUT_PP;
    LED_Init_Struct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOF,&LED_Init_Struct);

    HAL_GPIO_WritePin(LED_IO, GPIO_PIN_SET);
}
void ledToggle(void) {
    HAL_GPIO_TogglePin(LED_IO);
}
void ledOn(void) {
    HAL_GPIO_WritePin(LED_IO, GPIO_PIN_RESET);
}
void ledOff(void) {
    HAL_GPIO_WritePin(LED_IO, GPIO_PIN_SET);
}

