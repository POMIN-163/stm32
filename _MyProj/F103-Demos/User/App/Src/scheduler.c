#include "scheduler.h"

volatile uint32_t gTime0 = 0;
volatile uint32_t gTime1 = 0;

#define CLK_TYPE volatile uint32_t      // 定义调度器时钟依赖的计时变量数据类型
#define CLK_TICK (gTime0)               // 定义调度器时钟到一个计时变量上面

static taskTypeDef* head_handle = _NULL_;
/**
 * @brief 调度器载入一项任务 (单链表倒序插入)
 *
 * @param handle 任务指针
 * @return int
**/
uint8_t schedulerLoad(taskTypeDef* handle, uint32_t cycleLength, uint8_t isRepeat, Func timeoutTask) {
    taskTypeDef* target = head_handle;
    handle->cycle  = cycleLength;
    handle->task   = timeoutTask;
    handle->repeat = isRepeat;
    handle->lastRun= 0;
    handle->runTime= 0;
    while(target) {
        if(target == handle)
            return 1;       // 已经存在
        target = target->next;
    }
    handle->next = head_handle;
    head_handle  = handle;
    return 0;
}
/**
 * @brief 调度器删除一项任务 (二级指针遍历任务表)
 *
 * @param handle 任务指针
**/
uint8_t schedulerDel(taskTypeDef* handle) {
    taskTypeDef** curr;
    for(curr = &head_handle; *curr;) {
        taskTypeDef* entry = *curr;
        if(entry == handle) {
            *curr = entry->next;
            return 0;
        }
        else
            curr = &entry->next;
    }
    return 1;
}
/**
 * @brief 调度器工作 (单链表遍历)
 *
**/
void schedulerRun(void) {
    taskTypeDef* target;
    CLK_TYPE timeTemp = CLK_TICK;
    for(target = head_handle; target; target = target->next) {
        if(timeTemp > (target->lastRun + target->cycle)) {
            if(target->repeat == 0) {
                schedulerDel(target);
            } else {
                target->lastRun = timeTemp;
            }
            target->task();
            target->runTime = CLK_TICK - timeTemp;
        }
    }
}
/**
 * @brief 调度器时钟工作
 *
**/
void schedulerTick(void) {
    CLK_TICK++;
}


