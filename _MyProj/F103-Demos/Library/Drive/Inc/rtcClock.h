#ifndef __RTCCLOCK_H
#define __RTCCLOCK_H
#include "system.h"

extern RTC_TimeTypeDef timeNow;
extern RTC_DateTypeDef dateNow;

uint8_t rtcClockInit(void);
void rtcClockUpdate(void);

#endif
