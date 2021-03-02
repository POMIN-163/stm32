#include "main.h"

char printLCDBuff[100];
#define printLCD(line, format, ...)                         \
    sprintf(&printLCDBuff[0], format, ##__VA_ARGS__);       \
    OLED_ShowString(8, line * 24, (u8 *)printLCDBuff, 16); \
    OLED_Refresh()

static void systemClockOn(void);
static void systemCallFun(void);

/**
 * @brief ʱ�ӳ�ʼ��
 *
**/
static void systemClockOn(void) {
    timBaseConf(TIM4, 72, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(TIM4_IRQn, 0x01, 0x02);
}
/**
 * @brief ����ָ�����
 *
**/
void systemCallFun(void) {
    keyFun[0] = _NULL_;
}
/**
 * @brief 2ms��������
 *
**/
taskTypeDef task2MS;
void TASK_CYCLE_2MS(void) {

}
taskTypeDef task10MS;
void TASK_CYCLE_10MS(void) {
    printLCD(0, "Time: %d s", gTime0 / 1000);
}
/**
 * @brief 500ms��������
 *
**/
taskTypeDef task500MS;
void TASK_CYCLE_500MS(void) {
    ledToggle();
    keyRun();
}
uint8_t statusInit = 0;
/**
 * @brief ��ʼ��
 *
**/
uint8_t Init(void) {
    //------------------ �������ʼ�� -----------------//
    nvicGroupConf(NVIC_PriorityGroup_2);
    sysConf(72, 1);       // systick ����
    ledInit();            // led
    debugInit(115200);    // ���Դ���
    keyInit();            // ����
    systemClockOn();      // ʱ��Ƭ��
    systemCallFun();      // ��Ӧ����
    OLED_Init();          // oled ��ʼ��
    breathLedInit();      // ������
    //------------------ ģ���ʼ�� -------------------//
    //
    //------------------ Ӧ�ó�ʼ�� -------------------//
    schedulerLoad(&task2MS, 2, 1, TASK_CYCLE_2MS);
    schedulerLoad(&task10MS,10, 1, TASK_CYCLE_10MS);
    schedulerLoad(&task500MS, 500, 1, TASK_CYCLE_500MS);           // ������ȳ�ʼ��
    commandInit();                                                 // Shell ��ʼ��
    cm_backtrace_init(APPNAME, HARDWARE_VERSION, SOFTWARE_VERSION);// �������س�ʼ��
    if (statusInit) {
        printErr("Init have errors: %d", statusInit);
    }
    return 0;
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
void TIM4_IRQHandler() {
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
        schedulerTick();
        keyScan();
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}
void SysTick_Handler(void) {
    gTime1++;
}
