#include "device.h"

static void systemClockOn(void);
static void systemCallFun(void);

#define task_num (7)
typedef struct {
    void(*task)(void);
    unsigned long int cycle_length;
    unsigned long int last_run;
    unsigned long int run_time;
} task_s;
volatile unsigned long int gTime = 0;
volatile unsigned long int gTime1 = 0;
unsigned char scheduler_index;

void beepon(void)  {
    beepOn();
    sysDelayMS(200);
    beepOff();
}
void reportTime(void) {
    print("VAL:%d ms %d us\r\n", captureTime[1], captureTime[0]);
}
void reportTouch(void) {
    print("Touch is Press\r\n");
}
void reportExti(void) {
    print("EXTI is Press\r\n");
}
void reportInit(void) {
    print("Touch Key: %d\n", touchDefult); // �������� Ĭ��ֵ
    print("LCD ID: %x\n", lcddev.id);  // ��ӡ LCD ID
}
void reportDebug(void) {
    printf("%s\n", debugRxBuff);
}
void Init(void) {
    //------------------ �������ʼ�� -------------------//
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
    reportInit();         // �ϱ���ʼ��״̬
    //------------------ ģ���ʼ�� -------------------//
    // hcsr04Init();      // ������������
}
static void systemClockOn(void) {
    timBaseConf(TIM10, 168, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(TIM1_UP_TIM10_IRQn, 0x01, 0x02);
}
static void systemCallFun(void) {
    keyFun[0] = beepon;
    keyFun[KEY_EXTI0] = reportExti;
    touchkeyFun = reportTouch;
    debugFun = reportDebug;
}
static void TASK_CYCLE_1MS(void) {
}
static void TASK_CYCLE_2MS(void) {
    keyScan();
    touchScan();
}
static void TASK_CYCLE_5MS(void) {

}
static void TASK_CYCLE_10MS(void) {

}
static void TASK_CYCLE_100MS(void) {
}
static void TASK_CYCLE_200MS(void) {
}
static void TASK_CYCLE_500MS(void) {
    ledToggle();
    keyRun();
    touchRun();
    debugReply();
    printf("Time1: %d, Time2: %d\n", gTime, gTime1);
    // print("HC-SR04_Distance: %d\r\n", hcsr04GetLength());
}
static task_s systemTasks[] = {
    {TASK_CYCLE_1MS  , 1,   0, 0},
    {TASK_CYCLE_2MS  , 2,   0, 0},
    {TASK_CYCLE_5MS  , 5,   0, 0},
    {TASK_CYCLE_10MS , 10,  0, 0},
    {TASK_CYCLE_100MS, 100, 0, 0},
    {TASK_CYCLE_200MS, 200, 0, 0},
    {TASK_CYCLE_500MS, 500, 0, 0},
};
int main(void) {
    Init();
    for(scheduler_index = 0; scheduler_index < task_num; scheduler_index++) {
        if(systemTasks[scheduler_index].cycle_length < 1) {
            systemTasks[scheduler_index].cycle_length = 1;
        }
    }
    while (true) {
        for(scheduler_index = 0; scheduler_index < task_num; scheduler_index++) {
            if(gTime - systemTasks[scheduler_index].last_run >= systemTasks[scheduler_index].cycle_length) {
                systemTasks[scheduler_index].last_run=gTime;
                systemTasks[scheduler_index].task();
            }
        }
    }
}
// ʱ������
void TIM1_UP_TIM10_IRQHandler() {
    if(TIM_GetITStatus(TIM10, TIM_IT_Update) != RESET) {
        gTime1++;
        TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
    }
}

void SysTick_Handler(void) {
    gTime++;
}
