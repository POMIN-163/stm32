#include "scheduler.h"

volatile uint32_t gTime0 = 0;
volatile uint32_t gTime1 = 0;

#define CLK_TYPE volatile uint32_t      // ���������ʱ�������ļ�ʱ������������
#define CLK_TICK (gTime0)               // ���������ʱ�ӵ�һ����ʱ��������

static taskTypeDef* head_handle = _NULL_;
/**
 * @brief ����������һ������ (�����������)
 *
 * @param handle ����ָ��
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
            return 1;       // �Ѿ�����
        target = target->next;
    }
    handle->next = head_handle;
    head_handle  = handle;
    return 0;
}
/**
 * @brief ������ɾ��һ������ (����ָ����������)
 *
 * @param handle ����ָ��
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
 * @brief ���������� (���������)
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
 * @brief ������ʱ�ӹ���
 *
**/
void schedulerTick(void) {
    CLK_TICK++;
}


