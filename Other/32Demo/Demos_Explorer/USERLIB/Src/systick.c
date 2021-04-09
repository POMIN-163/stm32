#include "systick.h"

static uint32_t systickFreq = 0;               // 1us��ʱ������

#if 1
// û�� SysTick_Config(); �汾
void sysConf(uint32_t sysFreq, uint8_t isDiv) {
    if(isDiv) {
        SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
        systickFreq = sysFreq/8;
    } else {
        SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
        systickFreq = sysFreq;
    }
}
void sysDelayUS(uint32_t us) {
    if(!systickFreq) return;
    SysTick->LOAD = us * systickFreq; 	  	   // ʱ�����
    SysTick->VAL = 0x00;        		       // ��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; // ��ʼ����
    while( !((SysTick->CTRL) & (1<<16)) );
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // �رռ�����
    SysTick->VAL = 0X00;       				   // ��ռ�����
}
void sysDelayMS(uint32_t ms) {
    uint32_t i;
    if(!systickFreq) return;
    for(i = 0; i < ms; i++) {
        sysDelayUS(1000);
    }
}

#else
// SysTick_Config(); �汾
void sysConf(uint32_t sysFreq, uint8_t isDiv) {
    systickFreq = sysFreq;                       // SysTick_Config();������ʱ��Դ
}
void sysDelayUS(uint32_t us) {
	uint32_t i;
    if(!systickFreq) return;
	SysTick_Config(systickFreq);                 // ϵͳ����ֵװ��
	for(i = 0; i < us; i++) {
		while( !((SysTick->CTRL) & (1<<16)) );   // �ȴ�us��
	}
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;  // �رռ�����
}
void sysDelayMS(uint32_t ms) {
	uint32_t i;
    if(!systickFreq) return;
	SysTick_Config(systickFreq * 1000);          // ϵͳ����ֵװ��
	for(i = 0; i < ms; i++) {
		while( !((SysTick->CTRL) & (1<<16)) );   // �ȴ�ms��
	}
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;  // �رռ�����
}
#endif
