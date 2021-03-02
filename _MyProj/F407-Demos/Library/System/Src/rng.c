#include "rng.h"
/**
 * @brief 初始化随机数发生器
 *
 * @return uint8_t 错误码
**/
uint8_t rngConf(void) {
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
    RNG_Cmd(ENABLE);
    sysDelayMS(10);
    if(RNG_GetFlagStatus(RNG_FLAG_DRDY) != SET) {   //等待随机数就绪
        sysDelayMS(100);
        if(RNG_GetFlagStatus(RNG_FLAG_DRDY) != SET) {
            return 1;
        }
    }
    return 0;
}
/**
 * @brief 获取随机数
 *
 * @param min 区间下限
 * @param max 区间上限
 * @return uint32_t 结果
**/
uint32_t rngGetRand(uint32_t min, uint32_t max) {
    uint32_t diff = max - min + 1;
    while(RNG_GetFlagStatus(RNG_FLAG_DRDY) != SET);
    return (RNG_GetRandomNumber() % diff + min);
}

