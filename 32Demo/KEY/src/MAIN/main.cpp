#include "Led..Beep..Key.h"
#include "Class_GPIO.h"
#include "Class_Sys.h"

Class_GPIO gpio;// GPIO 操作类
Class_SYS sys;// 系统操作类

void Init_GPIO(){
    gpio.Clock(RCC_AHB1Periph_GPIOF, ENABLE);
    gpio.Config(// LED
        GPIOF
        ,GPIO_Pin_9|GPIO_Pin_10
        ,GPIO_Mode_OUT
        ,GPIO_Speed_100MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
    );
    gpio.Clock(RCC_AHB1Periph_GPIOE, ENABLE);
    gpio.Config(// KEY
        GPIOE
        ,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4
        ,GPIO_Mode_IN
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
    );
    gpio.Clock(RCC_AHB1Periph_GPIOA, ENABLE);
    gpio.Config(
        GPIOA
        ,GPIO_Pin_1
        ,GPIO_Mode_IN
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_DOWN
    );
	  // BEEP
    gpio.Config(
        GPIOF
        ,GPIO_Pin_8
        ,GPIO_Mode_OUT
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_DOWN
    );
}
void Init_Sys(){
    sys.Init(SysTick_CLKSource_HCLK_Div8, 168);
}
int main(void){
    u8 Key;
    Init_GPIO();
    Init_Sys();
    while(1){
        Key = key_Scan(0, 20);
        if(Key)
            switch(Key){
                case 1 : LED1 = ~LED1; break;
                case 2 : LED2 = ~LED2; break;
                case 3 : LED2 = ~LED2; LED1 = ~LED1; break;
                case 4 : BEEP = ~BEEP; break;
                default: break;
            }
            else{
                sys.Delay_ms(20);
        }
    }
}
