#include "xwdg.h"

// ��ʼ���������Ź�
void IWDG_Init(u8 prer,u16 rlr) {
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(prer); // IWDG ��Ƶϵ��
    IWDG_SetReload(rlr);     // IWDG װ��ֵ
    IWDG_ReloadCounter();    // �����װ��ֵ
    IWDG_Enable();           // ʹ�ܿ��Ź�
}
// ι�������Ź�
void IWDG_Feed(void) {
    IWDG_ReloadCounter();
}
//����WWDG������������ֵ,Ĭ��Ϊ���.
u8 WWDG_CNT = 0X7F;
// ��ʼ�����ڿ��Ź�
// tr: T[6:0],������ֵ
// wr: W[6:0],����ֵ
// fprer:��Ƶϵ����WDGTB��,�����2λ��Ч
// Fwwdg = PCLK1/(4096*2^fprer). һ��PCLK1=42Mhz
void WWDG_Init(u8 tr, u8 wr,u32 fprer) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); //ʹ�ܴ��ڿ��Ź�ʱ��

    WWDG_CNT = tr & WWDG_CNT;  // ��ʼ��WWDG_CNT
    WWDG_SetPrescaler(fprer);  // ���÷�Ƶֵ
    WWDG_SetWindowValue(wr);   // ���ô���ֵ
//  WWDG_SetCounter(WWDG_CNT); // ���ü���ֵ
    WWDG_Enable(WWDG_CNT);     // �������Ź�
    nvicIRQConf(WWDG_IRQn, 2, 2);

    WWDG_ClearFlag(); //�����ǰ�����жϱ�־λ
    WWDG_EnableIT();  //������ǰ�����ж�
}
//���ڿ��Ź��жϷ������
void WWDG_IRQHandler(void) {
    WWDG_SetCounter(WWDG_CNT); // ���贰�ڿ��Ź�ֵ
    WWDG_ClearFlag();          // �����ǰ�����жϱ�־λ
}
