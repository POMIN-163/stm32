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
unsigned char scheduler_index;

void beepon(void)  {
    beepOn();
    sysDelayMS(200);
    beepOff();
}
void reportTime(void) {
    printf("VAL:%d ms %d us\r\n", captureTime[1], captureTime[0]);
}
void reportTouch(void) {
    printf("Touch is Press\r\n");
}
void reportExti(void) {
    printf("EXTI is Press\r\n");
}
void reportInit(void) {
    printf("Touch Key: %d", touchDefult); // 触摸按键 默认值
    printf("LCD ID: %x\r\n", lcddev.id);  // 打印 LCD ID
}
void Init(void) {
    //------------------ 开发板初始化 -------------------//
    nvicGroupConf(NVIC_PriorityGroup_2);
    sysConf(168, 1);      // systick 配置
    ledInit();            // led
    keyInit();            // 按键
    beepInit();           // 蜂鸣器
    uart_init(115200);    // 调试串口
    touchInit();          // 触摸按键
    LCD_Init();           // LCD 显示屏
    systemClockOn();      // 时钟片轮
    systemCallFun();      // 响应函数挂载
    breathLedInit();      // 呼吸灯
    reportInit();         // 上报初始化状态
    //------------------ 模块初始化 -------------------//
    // hcsr04Init();      // 超声波传感器
}
static void systemClockOn(void) {
    timBaseConf(TIM10, 84, 1000, TIM_CounterMode_Up, TIM_CKD_DIV1);
    nvicIRQConf(TIM1_UP_TIM10_IRQn, 0x01, 0x02);
}
static void systemCallFun(void) {
    keyFun[0] = beepon;
    keyFun[KEY_EXTI0] = reportExti;
    touchkeyFun = reportTouch;
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
    ledToggle(LED1);
    keyRun();
    touchRun();
    // printf("HC-SR04_Distance: %d\r\n", hcsr04GetLength());
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
// 时钟心跳
void TIM1_UP_TIM10_IRQHandler() {
    if(TIM_GetITStatus(TIM10, TIM_IT_Update) != RESET) {
        gTime++;
        TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
    }
}
