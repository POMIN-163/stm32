#ifndef __APP_H
#define __APP_H
// device.h Ϊ������, ���ļ�Ϊ����������������㿪���� App

#define APPNAME                        "POMIN F407"
#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.0.1"

#include "scheduler.h"      // �������
#include "command.h"        // Shell �� log ��־��
#include "cm_backtrace.h"   // ���������Դ������� (HardFault_Handler)

#endif
