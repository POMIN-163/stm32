#include "Led..Beep..key.hpp"
#include "Class_Sys.hpp"

u8 key_Scan(u8 mode, u8 delay) {
    static u8 key_up = 1; // �������ɿ���־
    if(mode) key_up = 1;  // mode==1,֧������,key_up��Զ��1,ʹ���йص�key_up�޹ػ�
    if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1)) {
        _SYS_Delay_ms(10);
        key_up=0;
        if(KEY0 == 0) return 1;
        else if(KEY1 == 0) return 2;
        else if(KEY2 == 0) return 3;
        else if(WK_UP == 1) return 4;
    }
    else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0)
        key_up=1;
    return 0;// �ް�������
}
