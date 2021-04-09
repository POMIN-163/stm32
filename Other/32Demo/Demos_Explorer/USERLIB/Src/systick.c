#include "systick.h"

static uint32_t systickFreq = 0;               // 1us延时倍乘数

#if 1
// 没用 SysTick_Config(); 版本
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
    SysTick->LOAD = us * systickFreq; 	  	   // 时间加载
    SysTick->VAL = 0x00;        		       // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; // 开始倒数
    while( !((SysTick->CTRL) & (1<<16)) );
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
    SysTick->VAL = 0X00;       				   // 清空计数器
}
void sysDelayMS(uint32_t ms) {
    uint32_t i;
    if(!systickFreq) return;
    for(i = 0; i < ms; i++) {
        sysDelayUS(1000);
    }
}

#else
// SysTick_Config(); 版本
void sysConf(uint32_t sysFreq, uint8_t isDiv) {
    systickFreq = sysFreq;                       // SysTick_Config();会配置时钟源
}
void sysDelayUS(uint32_t us) {
	uint32_t i;
    if(!systickFreq) return;
	SysTick_Config(systickFreq);                 // 系统计数值装载
	for(i = 0; i < us; i++) {
		while( !((SysTick->CTRL) & (1<<16)) );   // 等待us次
	}
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;  // 关闭计数器
}
void sysDelayMS(uint32_t ms) {
	uint32_t i;
    if(!systickFreq) return;
	SysTick_Config(systickFreq * 1000);          // 系统计数值装载
	for(i = 0; i < ms; i++) {
		while( !((SysTick->CTRL) & (1<<16)) );   // 等待ms次
	}
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;  // 关闭计数器
}
#endif
