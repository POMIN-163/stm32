#include "main.h"

char printLCDBuff[100];
#define printLCD(line, format, ...)                         \
    sprintf(&printLCDBuff[0], format, ##__VA_ARGS__);       \
    LCD_ShowString(30, line * 24, 400, 24, 24, (u8 *)printLCDBuff)

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
void systemCallFun(void) {
    keyFun[0] = (Func)beepOnce;
}
/**
 * @brief 2ms��������
 *
**/
taskTypeDef task2MS;
void TASK_CYCLE_2MS(void) {
    keyScan();
    touchScan();
    printInfo("Length: %d, 0", hcsr04GetLength());
}
taskTypeDef task10MS;
void TASK_CYCLE_10MS(void) {
    rtcClockUpdate();
    printLCD(1, "Date: %04d - %02d - %02d", dateNow.RTC_Year+2000, dateNow.RTC_Month, dateNow.RTC_Date);
    printLCD(1, "Week: %d", dateNow.RTC_WeekDay);
    printLCD(2, "Time: %02d:%02d:%02d", timeNow.RTC_Hours, timeNow.RTC_Minutes, timeNow.RTC_Seconds);
    // printDbg("Y: %d, M: %d, D: %d, WEEK: %d", year, mouth, date, weekday);
}
/**
 * @brief 500ms��������
 *
**/
taskTypeDef task500MS;
void TASK_CYCLE_500MS(void) {
    printLCD(3, "Rand[0 - 0xff]: %x", rngGetRand(0, 0xffff));
    ledToggle();
    keyRun();
    touchRun();
}
uint8_t statusInit = 0;
/**
 * @brief ��ʼ��
 *
**/
uint8_t Init(void) {
    //------------------ �������ʼ�� -----------------//
    nvicGroupConf(NVIC_PriorityGroup_2);
    sysConf(168, 1);      // systick ����
    debugInit(115200);    // ���Դ���
    ledInit();            // led
    keyInit();            // ����
    beepInit();           // ������
    LCD_Init();           // LCD ��
    rtcClockInit();       // RTC ʱ��
    rngConf();            // �����������
    touchInit();          // ��������
    systemClockOn();      // ʱ��Ƭ��
    systemCallFun();      // ��Ӧ����
    breathLedInit();      // ������
    //------------------ ģ���ʼ�� -------------------//
    hcsr04Init();      // ������������
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
void TIM1_UP_TIM10_IRQHandler() {
    if(TIM_GetITStatus(TIM10, TIM_IT_Update) != RESET) {
        schedulerTick();
        TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
    }
}
void SysTick_Handler(void) {
    gTime1++;
}
