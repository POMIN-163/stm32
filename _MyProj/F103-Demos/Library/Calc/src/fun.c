#include "fun.h"
/**
 * @brief ȡ����ֵ
 *
 * @param value    ԭֵ
 * @return int32_t ����ֵ
**/
int32_t funAbs(int32_t value) {
    if(value < 0) {
        value = -value;
    }
    return value;
}
/**
 * @brief �޷�����
 *
 * @param value    ԭֵ
 * @param min      ����
 * @param max      ����
 * @return int32_t ���
**/
int32_t funLimit(int32_t value, int32_t min, int32_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
