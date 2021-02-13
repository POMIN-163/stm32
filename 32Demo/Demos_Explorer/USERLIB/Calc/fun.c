#include "fun.h"

int32_t funAbs(int32_t value) {
    if(value < 0) {
        value = -value;
    }
    return value;
}
