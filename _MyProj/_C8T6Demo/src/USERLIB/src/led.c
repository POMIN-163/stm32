#include "led.h"

#define LED_GPIO GPIOC
#define LED_PIN GPIO_Pin_13
#define LED_CLK RCC_APB2Periph_GPIOC

#define LED_OUT PCout(13)

static void _GPIO_Config(
    GPIO_TypeDef* GPIOx,
    uint32_t GPIO_Pin,
    GPIOMode_TypeDef GPIO_Mode,
    GPIOSpeed_TypeDef GPIO_Speed
) {
    GPIO_InitTypeDef Temp;
		Temp.GPIO_Pin = GPIO_Pin;
		Temp.GPIO_Mode = GPIO_Mode;
        Temp.GPIO_Speed = GPIO_Speed;
    GPIO_Init(GPIOx, &Temp);
}
void LED_Init(void) {
    RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);
    _GPIO_Config(LED_GPIO, LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}
void LED_Toggle(void) {
    LED_OUT = !LED_OUT;
}
