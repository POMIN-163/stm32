#include "rng.h"
/**
 * @brief ��ʼ�������������
 *
 * @return uint8_t ������
**/
uint8_t rngConf(void) {
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
    RNG_Cmd(ENABLE);
    sysDelayMS(10);
    if(RNG_GetFlagStatus(RNG_FLAG_DRDY) != SET) {   //�ȴ����������
        sysDelayMS(100);
        if(RNG_GetFlagStatus(RNG_FLAG_DRDY) != SET) {
            return 1;
        }
    }
    return 0;
}
/**
 * @brief ��ȡ�����
 *
 * @param min ��������
 * @param max ��������
 * @return uint32_t ���
**/
uint32_t rngGetRand(uint32_t min, uint32_t max) {
    uint32_t diff = max - min + 1;
    while(RNG_GetFlagStatus(RNG_FLAG_DRDY) != SET);
    return (RNG_GetRandomNumber() % diff + min);
}

