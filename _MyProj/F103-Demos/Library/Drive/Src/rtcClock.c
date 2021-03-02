#include "rtcClock.h"

RTC_TimeTypeDef timeNow;
RTC_DateTypeDef dateNow;

/**
 * @brief 初始化闹钟
 *
 * @return uint8_t 错误码
**/
uint8_t rtcClockInit(void) {
    uint8_t errors = 0;
    errors = rtcConf(RTC_HourFormat_24, 0x7F, 0xFF, _NULL_);
    wakeConf(RTC_WakeUpClock_CK_SPRE_16bits, 0);                     // 一秒一次唤醒
    //rtcAlarmConf(timeNow.RTC_Hours, timeNow.RTC_Minutes+10, timeNow.RTC_Seconds, false, 0);
    extiConf(EXTI_Line17, EXTI_Mode_Interrupt, EXTI_Trigger_Rising); // 配置闹钟中断
    nvicIRQConf(RTC_Alarm_IRQn, 0x02, 0x02);
    extiConf(EXTI_Line22, EXTI_Mode_Interrupt, EXTI_Trigger_Rising); // 配置唤醒中断
    nvicIRQConf(RTC_WKUP_IRQn, 0x02, 0x02);
    return errors;
}
/**
 * @brief 更新时间
 *
**/
void rtcClockUpdate(void) {
    rtcGetTime(&timeNow, &dateNow);
}

// RTC闹钟 A 中断服务函数
void RTC_Alarm_IRQHandler(void) {
    if (RTC_GetFlagStatus(RTC_FLAG_ALRAF) == SET) {

        RTC_ClearFlag(RTC_FLAG_ALRAF);
    }
    EXTI_ClearITPendingBit(EXTI_Line17);
}

// RTC WAKE UP中断服务函数
void RTC_WKUP_IRQHandler(void) {
    if (RTC_GetFlagStatus(RTC_FLAG_WUTF) == SET) {
        RTC_ClearFlag(RTC_FLAG_WUTF);
    }
    EXTI_ClearITPendingBit(EXTI_Line22);
}
