#include "fun.h"
/**
 * @brief 取绝对值
 *
 * @param value    原值
 * @return int32_t 绝对值
**/
int32_t funAbs(int32_t value) {
    if(value < 0) {
        value = -value;
    }
    return value;
}
/**
 * @brief 限幅函数
 *
 * @param value    原值
 * @param min      下限
 * @param max      上限
 * @return int32_t 结果
**/
int32_t funLimit(int32_t value, int32_t min, int32_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
