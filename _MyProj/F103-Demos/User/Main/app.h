#ifndef __APP_H
#define __APP_H
// device.h 为驱动层, 本文件为包含各类基于驱动层开发的 App

#define APPNAME                        "POMIN F407"
#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.0.1"

#include "scheduler.h"      // 任务调度
#include "command.h"        // Shell 和 log 日志类
#include "cm_backtrace.h"   // 代码致命性错误拦截 (HardFault_Handler)

#endif
