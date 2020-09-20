#include "key.h"

void key_Init(){
    GPIO_InitTypeDef KEY_Init;// 结构体

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    // key0、1、3时钟初始化
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    // key_up时钟初始化

    /******key0-2初始化******/
        KEY_Init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;

        KEY_Init.GPIO_Mode = GPIO_Mode_IN;
        // 普通输入模式
        KEY_Init.GPIO_Speed = GPIO_Speed_100MHz;
        // 100MHz
        KEY_Init.GPIO_PuPd = GPIO_PuPd_UP;
        // 上拉
        GPIO_Init(GPIOE,&KEY_Init);
        // 初始化
    /******wk_up初始化******/
        KEY_Init.GPIO_Pin = GPIO_Pin_0;
        // 脚0
        KEY_Init.GPIO_PuPd = GPIO_PuPd_DOWN;
        // 下拉(默认低电平)
        GPIO_Init(GPIOA, &KEY_Init);

}
// 参数大于0则支持连按,等于0则不支持连按
u8 key_Scan(u8 mode){
    static u8 key_up = 1;// 按键按松开标志
    if(mode)key_up = 1;  // 如果mode==1,支持连按,key_up永远是1,使得有关的key_up无关化
    if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
    {
        delay_ms(10);// 去抖动
        key_up=0;
        if(KEY0 == 0)
            return 1;
        else if(KEY1 == 0)
            return 2;
        else if(KEY2 == 0)
            return 3;
        else if(WK_UP == 1)
            return 4;
    }
      else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0)
            key_up=1;
     return 0;// 无按键按下
}
