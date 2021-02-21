#include "main.h"

static void systemClockOn(void);
static void systemCallFun(void);

/**
 * @brief ʱ�ӳ�ʼ��
 *
**/
static void systemClockOn(void) {
    timBaseConf(TIM10, 168, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(TIM1_UP_TIM10_IRQn, 0x01, 0x02);
}
/**
 * @brief ����ָ�����
 *
**/
static void systemCallFun(void) {
    keyFun[0] = beepOnce;
}
/**
 * @brief 2ms��������
 *
**/
taskTypeDef task2MS;
static void TASK_CYCLE_2MS(void) {
    keyScan();
    touchScan();
}
/**
 * @brief 500ms��������
 *
**/
taskTypeDef task500MS;
void TASK_CYCLE_500MS(void) {
    ledToggle();
    keyRun();
    touchRun();
}
void Init(void) {
    //------------------ �������ʼ�� -----------------//
    nvicGroupConf(NVIC_PriorityGroup_2);
    sysConf(168, 1);      // systick ����
    debugInit(115200);    // ���Դ���
    ledInit();            // led
    keyInit();            // ����
    beepInit();           // ������
    LCD_Init();           // LCD ��
    touchInit();          // ��������
    systemClockOn();      // ʱ��Ƭ��
    systemCallFun();      // ��Ӧ����
    breathLedInit();      // ������
    //------------------ ģ���ʼ�� -------------------//
    // hcsr04Init();      // ������������
    //------------------ Ӧ�ó�ʼ�� -------------------//
    schedulerLoad(&task2MS, 2, 1, TASK_CYCLE_2MS);
    schedulerLoad(&task500MS, 500, 1, TASK_CYCLE_500MS);           // ������ȳ�ʼ��
    commandInit();                                                 // Shell ��ʼ��
    cm_backtrace_init(APPNAME, HARDWARE_VERSION, SOFTWARE_VERSION);// �������س�ʼ��
    //------------------------------------------------//
}

/**
 * @brief ������
 *
 * @return int
**/
int main(void) {
    Init();
    while (true) {
        schedulerRun();
    }
}
/**
 * @brief ʱ������
 *
**/
void TIM1_UP_TIM10_IRQHandler() {
    if(TIM_GetITStatus(TIM10, TIM_IT_Update) != RESET) {
        // gTime0++;
        schedulerTick();
        TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
    }
}
void SysTick_Handler(void) {
    gTime1++;
}
