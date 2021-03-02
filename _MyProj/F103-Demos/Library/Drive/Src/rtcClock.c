#include "rtcClock.h"

RTC_TimeTypeDef timeNow;
RTC_DateTypeDef dateNow;

/**
 * @brief ��ʼ������
 *
 * @return uint8_t ������
**/
uint8_t rtcClockInit(void) {
    uint8_t errors = 0;
    errors = rtcConf(RTC_HourFormat_24, 0x7F, 0xFF, _NULL_);
    wakeConf(RTC_WakeUpClock_CK_SPRE_16bits, 0);                     // һ��һ�λ���
    //rtcAlarmConf(timeNow.RTC_Hours, timeNow.RTC_Minutes+10, timeNow.RTC_Seconds, false, 0);
    extiConf(EXTI_Line17, EXTI_Mode_Interrupt, EXTI_Trigger_Rising); // ���������ж�
    nvicIRQConf(RTC_Alarm_IRQn, 0x02, 0x02);
    extiConf(EXTI_Line22, EXTI_Mode_Interrupt, EXTI_Trigger_Rising); // ���û����ж�
    nvicIRQConf(RTC_WKUP_IRQn, 0x02, 0x02);
    return errors;
}
/**
 * @brief ����ʱ��
 *
**/
void rtcClockUpdate(void) {
    rtcGetTime(&timeNow, &dateNow);
}

// RTC���� A �жϷ�����
void RTC_Alarm_IRQHandler(void) {
    if (RTC_GetFlagStatus(RTC_FLAG_ALRAF) == SET) {

        RTC_ClearFlag(RTC_FLAG_ALRAF);
    }
    EXTI_ClearITPendingBit(EXTI_Line17);
}

// RTC WAKE UP�жϷ�����
void RTC_WKUP_IRQHandler(void) {
    if (RTC_GetFlagStatus(RTC_FLAG_WUTF) == SET) {
        RTC_ClearFlag(RTC_FLAG_WUTF);
    }
    EXTI_ClearITPendingBit(EXTI_Line22);
}
