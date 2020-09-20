#include "Class_GPIO.h"
#include "Led..Key.h"

void Init(){
    Class_GPIO gpio;
    gpio.Clock(RCC_AHB1Periph_GPIOF, ENABLE);
    gpio.Setting(// LED
        GPIOF
        ,GPIO_Pin_9|GPIO_Pin_10
        ,GPIO_Mode_OUT
        ,GPIO_Speed_100MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
    );
    gpio.Clock(RCC_AHB1Periph_GPIOE, ENABLE);
    gpio.Setting(// KEY
        GPIOE
        ,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4
        ,GPIO_Mode_IN
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_UP
    );
    gpio.Clock(RCC_AHB1Periph_GPIOA, ENABLE);
    gpio.Setting(
        GPIOA
        ,GPIO_Pin_1
        ,GPIO_Mode_IN
        ,GPIO_Speed_50MHz
        ,GPIO_OType_PP
        ,GPIO_PuPd_DOWN
    );
}

int main(void){
    u8 Key;
    delay_init(168);
    Init();
    while(1){
        Key = key_Scan(0);
        if(Key)
            switch(Key){
                case 1 : led1 = ~led1;break;
                case 2 : led2 = ~led2;break;
                case 3 : led2 = ~led2;led1 = ~led1;break;
                case 4 : led1 = ~led1; led2 = ~led2;break;
                default: break;
            }else
        {
            delay_ms(20);
        }

        // gpio.SetBit(GPIOF, GPIO_Pin_9|GPIO_Pin_10, 1);
        // delay_ms(300);
        // gpio.SetBit(GPIOF, GPIO_Pin_9|GPIO_Pin_10, 0);
        // delay_ms(300);
    }
}
