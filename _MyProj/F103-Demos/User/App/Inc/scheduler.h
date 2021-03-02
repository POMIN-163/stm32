#ifndef __SCHEDULER_H
#define __SCHEDULER_H
#include "device.h"

typedef struct TaskType{
    Func task;
    uint8_t  repeat;
    uint32_t cycle;
    uint32_t lastRun;
    uint32_t runTime;
    struct TaskType *next;
} taskTypeDef;

uint8_t schedulerLoad(taskTypeDef* handle, uint32_t cycleLength, uint8_t isRepeat, Func timeoutTask);
uint8_t schedulerDel(taskTypeDef* handle);
void schedulerRun(void);
void schedulerTick(void);

#endif

