#include "sort.h"
/**
 * @brief 冒泡排序
 *
 * @param arr      数组头地址
 * @param length   数组成员数
 * @param mode     排序模式     0.升序排列 1.降序排列
 * @return uint8_t 运行标志     0.排序完成 1.模式错误
**/
uint8_t sortBubble16(int16_t *arr, uint8_t length, uint8_t mode) {
    uint8_t i = 0, j = 0;
    int16_t temp = 0;
    if (mode > 1) return 1;
    if(arr == (void*)0) return 2;
    switch(mode) {
    case 0:
        for (i = 0; i < length - 1; i++) {
            for (j = i + 1; j < length; j++) {
                if (arr[i] > arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        break;
    case 1:
        for (i = 0; i < length - 1; i++) {
            for (j = i + 1; j < length; j++) {
                if (arr[i] < arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        break;
    }
    return 0;
}
uint8_t sortBubble32(int32_t *arr, uint8_t length, uint8_t mode) {
    uint8_t i = 0, j = 0;
    int32_t temp = 0;
    if (mode > 1) return 1;
    if(arr == (void*)0) return 2;
    switch(mode) {
    case 0:
        for (i = 0; i < length - 1; i++) {
            for (j = i + 1; j < length; j++) {
                if (arr[i] > arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        break;
    case 1:
        for (i = 0; i < length - 1; i++) {
            for (j = i + 1; j < length; j++) {
                if (arr[i] < arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        break;
    }
    return 0;
}
