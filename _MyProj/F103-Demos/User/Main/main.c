#include "main.h"

char printLCDBuff[100];
#define printLCD(line, format, ...)                         \
    sprintf(&printLCDBuff[0], format, ##__VA_ARGS__);       \
    OLED_ShowString(8, line * 24, (u8 *)printLCDBuff, 16); \
    OLED_Refresh()

static void systemClockOn(void);
static void systemCallFun(void);

void setServo(int32_t duty1, int32_t duty2, int32_t duty3) {
    TIM_SetCompare2(TIM4, duty1);
    TIM_SetCompare3(TIM4, duty2);
    TIM_SetCompare4(TIM4, duty3);
    printDbg("D1:%2d, D2:%2d, D3:%2d", duty1, duty2, duty3);
    printLCD(1, "A:%2d B:%2d C:%2d", duty1, duty2, duty3);
}
SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC) |
    SHELL_CMD_DISABLE_RETURN, cServo, setServo, setServo(d1, d2, d3));
/**
 * @brief ʱ�ӳ�ʼ��
 *
**/
static void systemClockOn(void) {
    timBaseConf(TIM2, 72, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(TIM2_IRQn, 0x01, 0x02);
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
 * @brief 200ms��������
 *
**/
uint32_t light = 0;
taskTypeDef task100MS;
void TASK_CYCLE_100MS(void) {
    uint8_t i;
    for (i = 0; i < RGB_NUM; i++) {
            if(i == light || i == light + 1)
                rgbWrite_One(0, 0, 100);
            else
                rgbWrite_One(0, 0, 0);
    }
    light++;
    if (light >= RGB_NUM) light = 0;
    ledToggle();
}
/**
 * @brief 500ms��������
 *
**/
taskTypeDef task500MS;
void TASK_CYCLE_500MS(void) {
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
    servoInit();          // �����ͷ
    // rgbInit();            // rgb ��ʼ��
    breathLedInit();      // ������
    //------------------ ģ���ʼ�� -------------------//
    //
    //------------------ Ӧ�ó�ʼ�� -------------------//
    schedulerLoad(&task2MS, 2, 1, TASK_CYCLE_2MS);
    schedulerLoad(&task10MS,10, 1, TASK_CYCLE_10MS);
    // schedulerLoad(&task100MS, 100, 1, TASK_CYCLE_100MS);
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
void TIM2_IRQHandler() {
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        schedulerTick();
        keyScan();
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
void SysTick_Handler(void) {
    gTime1++;
}
