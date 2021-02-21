#include "command.h"

// 导出到命令列表里 s 开头是查询命令, c 开头是命令, t 开头是转换命令
Shell shell;
int8_t  _int8;
int16_t _int16;
int32_t _int32;
int32_t *_point;
SHELL_EXPORT_VAR(SHELL_CMD_PERMISSION(0) |
                        SHELL_CMD_TYPE(SHELL_TYPE_VAR_INT),   _int32, &_int32, _int32);
SHELL_EXPORT_VAR(SHELL_CMD_PERMISSION(0) |
                        SHELL_CMD_TYPE(SHELL_TYPE_VAR_SHORT), _int16, &_int16, _int16);
SHELL_EXPORT_VAR(SHELL_CMD_PERMISSION(0) |
                        SHELL_CMD_TYPE(SHELL_TYPE_VAR_CHAR),  _int8,  &_int8,  _int8);
SHELL_EXPORT_VAR(SHELL_CMD_PERMISSION(0) |
                        SHELL_CMD_TYPE(SHELL_TYPE_VAR_POINT), _point, &_point, _point);

void reportInit(void) {
    printInfo("Touch Val: %d", touchDefault); // 触摸按键 默认值
    printInfo("LCD ID: 0x%x", lcddev.id);     // 打印 LCD ID
}
void reportTime(void) {
    printInfo("Timer1: %d, Timer2: %d", gTime0, gTime1);
}
void conver(char cmd, int32_t value) {
    switch(cmd) {
    case 'o':
        printInfo("DEC: %d, OCT: 0%o", value, value);
        break;
    case 'h':
        printInfo("DEC: %d, HEX: 0x%x", value, value);
        break;
    default:
        printErr("error, 'o': OCT  'h': HEX");
        break;
    }
}
void lcdControl(char cmd, int32_t value) {

}
void testLog(uint8_t cmd) {
    switch (cmd) {
    case 'l':
        log_v("ELOG OK");
        log_a("ELOG OK");
        log_d("ELOG OK");
        log_e("ELOG OK");
        log_i("ELOG OK");
        log_w("ELOG OK");
        break;
    default:
        printErr("error, 'l': TEST ELOG OUT");
        break;
    }
}
#if 1 == USE_SHELL
SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC) |
    SHELL_CMD_DISABLE_RETURN, sTime, reportTime, runtime);
SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC) |
    SHELL_CMD_DISABLE_RETURN, sInit, reportInit, init status);
// 查询
SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC) |
    SHELL_CMD_DISABLE_RETURN, tConver, conver, conver);
// 转换
SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC) ,
    cLcd, LCD_Clear, LcdClear(uint16 color));
SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC) |
    SHELL_CMD_DISABLE_RETURN, cTest, testLog, test);
// 指令

#endif

void commandInit(void) {
#if 1 == USE_SHELL
    shell.write = putch;
    shellInit(&shell, (char *)debugRxBuff, DEBUG_MAX_LEN);
    // 启动 lettleShell
#endif
#if 1== USE_ELOG
    elog_init();
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL& ~(ELOG_FMT_TIME| // 除了时间、进程信息、线程信息外全部输出
                 ELOG_FMT_P_INFO | ELOG_FMT_T_INFO));
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG);   // 使能输出错误
    elog_set_fmt(ELOG_LVL_WARN,  ELOG_FMT_LVL | ELOG_FMT_TAG);   // 使能输出警告
    elog_set_fmt(ELOG_LVL_INFO,  ELOG_FMT_LVL | ELOG_FMT_TAG);   // 使能输出信息
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_TIME| // 除了时间、进程信息、线程信息外全部输出
                 ELOG_FMT_P_INFO | ELOG_FMT_T_INFO));
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL);                // 输出所有内容
    elog_start();                                                // 启动 elog
    elog_set_text_color_enabled(true);                           // 使能多彩颜色
#endif
}
#if 0
/**
 * @brief 一个除 0 错误 (测试 cm_backtrace 用)
 *
**/
void fault_test_by_div0(void) {
    volatile int * SCB_CCR = (volatile int *) 0xE000ED14; // SCB->CCR
    int x, y, z;

    *SCB_CCR |= (1 << 4); /* bit4: DIV_0_TRP. */

    x = 10;
    y = 0;
    z = x / y;
    printf("z:%d\n", z);
}
SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)
    , error, fault_test_by_div0, error);
#endif

