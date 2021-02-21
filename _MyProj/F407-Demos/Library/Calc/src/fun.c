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
