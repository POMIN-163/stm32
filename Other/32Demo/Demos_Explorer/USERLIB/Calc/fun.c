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
