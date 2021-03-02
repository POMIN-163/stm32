#ifndef __RTC_H
#define __RTC_H
#include "stm32f4xx.h"

uint8_t rtcConf(uint32_t RTC_HourFormat, uint32_t AsynchPrediv,
                uint32_t SynchPrediv, uint8_t (*setTime)(void));
void rtcGetTime(RTC_TimeTypeDef *rtcTime, RTC_DateTypeDef *rtcDate);
void rtcAlarmConf(uint8_t AlarmHour, uint8_t AlarmMinutes, uint8_t AlarmSeconds,
                  uint8_t IsAlarmWeek, uint8_t AlarmDateWeekDay);
void wakeConf(uint32_t RTC_WakeUpClock, uint32_t wakeCnt);

#endif
