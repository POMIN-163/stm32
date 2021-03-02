#include "main.h"

char printLCDBuff[100];
#define printLCD(line, format, ...)                         \
    sprintf(&printLCDBuff[0], format, ##__VA_ARGS__);       \
    OLED_ShowString(8, line * 24, (u8 *)printLCDBuff, 16); \
    OLED_Refresh()

static void systemClockOn(void);
static void systemCallFun(void);

/**
 * @brief 时钟初始化
 *
**/
static void systemClockOn(void) {
    timBaseConf(TIM4, 72, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(TIM4_IRQn, 0x01, 0x02);
}
/**
 * @brief 函数指针挂载
 *
**/
void systemCallFun(void) {
    keyFun[0] = _NULL_;
}
/**
 * @brief 2ms周期任务
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
 * @brief 500ms周期任务
 *
**/
taskTypeDef task500MS;
void TASK_CYCLE_500MS(void) {
    ledToggle();
    keyRun();
}
uint8_t statusInit = 0;
/**
 * @brief 初始化
 *
**/
uint8_t Init(void) {
    //------------------ 开发板初始化 -----------------//
    nvicGroupConf(NVIC_PriorityGroup_2);
    sysConf(72, 1);       // systick 配置
    ledInit();            // led
    debugInit(115200);    // 调试串口
    keyInit();            // 按键
    systemClockOn();      // 时钟片轮
    systemCallFun();      // 响应函数
    OLED_Init();          // oled 初始化
    breathLedInit();      // 呼吸灯
    //------------------ 模块初始化 -------------------//
    //
    //------------------ 应用初始化 -------------------//
    schedulerLoad(&task2MS, 2, 1, TASK_CYCLE_2MS);
    schedulerLoad(&task10MS,10, 1, TASK_CYCLE_10MS);
    schedulerLoad(&task500MS, 500, 1, TASK_CYCLE_500MS);           // 任务调度初始化
    commandInit();                                                 // Shell 初始化
    cm_backtrace_init(APPNAME, HARDWARE_VERSION, SOFTWARE_VERSION);// 错误拦截初始化
    if (statusInit) {
        printErr("Init have errors: %d", statusInit);
    }
    return 0;
    //------------------------------------------------//
}

/**
 * @brief 主函数
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
 * @brief 时钟心跳
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
