#include "key.h"
#define KEY_GPIO GPIOA
#define KEY_PIN GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2
#define KEY_CLK RCC_APB2Periph_GPIOA

#define KEY_GET(n) PAin(n)

static u8 Key_last[6] = {1, 1, 1, 1, 1, 1,};
// 上一次按键状态
static u8 Key_now[6];
// 按键现行状态

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

void KEY_Init(void) {
    RCC_APB2PeriphClockCmd(KEY_CLK, ENABLE);
    _GPIO_Config(GPIOA, KEY_PIN, GPIO_Mode_IPU, GPIO_Speed_50MHz);
}
void keyScan(u16 *Key_msg) {
    u8 i;
    *Key_msg = 0;
    for(i = 0; i < 3; i++){
        Key_last[i] = Key_now[i];
        Key_now[i] = KEY_GET(i);
        if( Key_now[i] && !Key_last[i]) {
            *Key_msg |= 0x01 << i;
        }
    }
}
