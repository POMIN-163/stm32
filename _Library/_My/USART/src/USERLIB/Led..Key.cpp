#include "led..key.h"

u8 key_Scan(u8 mode){
    static u8 key_up = 1;// 按键按松开标志
    if(mode)key_up = 1;  // 如果mode==1,支持连按,key_up永远是1,使得有关的key_up无关化
    if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
    {
        delay_ms(10);// 去抖动
        key_up=0;
        if(KEY0 == 0) return 1;
        else if(KEY1 == 0) return 2;
        else if(KEY2 == 0) return 3;
        else if(WK_UP == 1) return 4;
    }
    else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0)
        key_up=1;
    return 0;// 无按键按下
}
