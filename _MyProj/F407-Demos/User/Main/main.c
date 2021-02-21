#include "main.h"

static void systemClockOn(void);
static void systemCallFun(void);

/**
 * @brief 时钟初始化
 *
**/
static void systemClockOn(void) {
    timBaseConf(TIM10, 168, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(TIM1_UP_TIM10_IRQn, 0x01, 0x02);
}
/**
 * @brief 函数指针挂载
 *
**/
static void systemCallFun(void) {
    keyFun[0] = beepOnce;
}
/**
 * @brief 2ms周期任务
 *
**/
taskTypeDef task2MS;
static void TASK_CYCLE_2MS(void) {
    keyScan();
    touchScan();
}
/**
 * @brief 500ms周期任务
 *
**/
taskTypeDef task500MS;
void TASK_CYCLE_500MS(void) {
    ledToggle();
    keyRun();
    touchRun();
}
void Init(void) {
    //------------------ 开发板初始化 -----------------//
    nvicGroupConf(NVIC_PriorityGroup_2);
    sysConf(168, 1);      // systick 配置
    debugInit(115200);    // 调试串口
    ledInit();            // led
    keyInit();            // 按键
    beepInit();           // 蜂鸣器
    LCD_Init();           // LCD 屏
    touchInit();          // 触摸按键
    systemClockOn();      // 时钟片轮
    systemCallFun();      // 响应函数
    breathLedInit();      // 呼吸灯
    //------------------ 模块初始化 -------------------//
    // hcsr04Init();      // 超声波传感器
    //------------------ 应用初始化 -------------------//
    schedulerLoad(&task2MS, 2, 1, TASK_CYCLE_2MS);
    schedulerLoad(&task500MS, 500, 1, TASK_CYCLE_500MS);           // 任务调度初始化
    commandInit();                                                 // Shell 初始化
    cm_backtrace_init(APPNAME, HARDWARE_VERSION, SOFTWARE_VERSION);// 错误拦截初始化
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
