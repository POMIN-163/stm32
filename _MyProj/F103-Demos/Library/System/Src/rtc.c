#include "rtc.h"

/**
 * @brief ��ȡ���ں�ʱ��
 *
 * @param rtcTime ʱ��ṹ��ָ��
 * @param rtcDate ���ڽṹ��ָ��
**/
void rtcGetTime(RTC_TimeTypeDef *rtcTime, RTC_DateTypeDef *rtcDate) {
    RTC_GetDate(RTC_Format_BIN, rtcDate);
    RTC_GetTime(RTC_Format_BIN, rtcTime);
}
/**
 * @brief ����Ϊ����ʱ��
 *
 * @return uint8_t [1]:ʱ�������Ƿ�ɹ�, [2]:���������Ƿ�ɹ�
**/
uint8_t setNowTime(void) {
    char strDate[20];                  // �����ַ���
    char strTime[20];                  // ʱ���ַ���
    int32_t year, mouth, date;         // ���ڲ���
    RTC_TimeTypeDef nowTime;
    RTC_DateTypeDef nowDate;
    sprintf(strDate, "%s", __DATE__);  // ��ʽ������ xxx xx xxxx
    sprintf(strTime, "%s", __TIME__);  // ��ʽ��ʱ�� xx:xx:xx
    strDate[3] = '\0';                 // �ָ�����
    strDate[6] = '\0';
    strTime[2] = '\0';                 // �ָ�ʱ��
    strTime[5] = '\0';
    if (strcmp(strDate, "Jan") == 0)      nowDate.RTC_Month = mouth = 1;
    else if (strcmp(strDate, "Feb") == 0) nowDate.RTC_Month = mouth = 2;
    else if (strcmp(strDate, "Mar") == 0) nowDate.RTC_Month = mouth = 3;
    else if (strcmp(strDate, "Apr") == 0) nowDate.RTC_Month = mouth = 4;
    else if (strcmp(strDate, "May") == 0) nowDate.RTC_Month = mouth = 5;
    else if (strcmp(strDate, "Jun") == 0) nowDate.RTC_Month = mouth = 6;
    else if (strcmp(strDate, "Jul") == 0) nowDate.RTC_Month = mouth = 7;
    else if (strcmp(strDate, "Aug") == 0) nowDate.RTC_Month = mouth = 8;
    else if (strcmp(strDate, "Sep") == 0) nowDate.RTC_Month = mouth = 9;
    else if (strcmp(strDate, "Oct") == 0) nowDate.RTC_Month = mouth = 10;
    else if (strcmp(strDate, "Nov") == 0) nowDate.RTC_Month = mouth = 11;
    else if (strcmp(strDate, "Dec") == 0) nowDate.RTC_Month = mouth = 12;
    else                                  nowDate.RTC_Month = mouth = 1;   // ��ȡ�·� (1~12)
    year = atoi(strDate + 4 + 3);
    nowDate.RTC_Year    = year - 2000;                                     // ��ȡ��� (0~99)
    nowDate.RTC_Date    = date = atoi(strDate + 4);                        // ��ȡ���� (0~31)
    if(mouth == 1 || mouth == 2) {
        mouth += 12; year--;                                               // ��ķ����ɭ��ʽ
    }
    nowDate.RTC_WeekDay =                                                  // ��ȡ���� (1~7)
        (date + 2 * mouth + 3 * (mouth + 1) / 5 + year + year / 4 - year / 100 +
         year / 400) % 7 + 1;
    nowTime.RTC_Hours   = atoi(strTime);                                   // ��ȡʱ��
    nowTime.RTC_Minutes = atoi(strTime + 3);
    nowTime.RTC_Seconds = atoi(strTime + 6);
    nowTime.RTC_H12     = RTC_H12_AM;                                      // 24 Сʱ��
    return ((uint8_t)!RTC_SetDate(RTC_Format_BIN, &nowDate) << 2) |
           ((uint8_t)!RTC_SetTime(RTC_Format_BIN, &nowTime) << 1);
}
/**
 * @brief ��ʼ�� RTC ʱ��
 *
 * @param RTC_HourFormat   ���ڸ�ʽ
 * @param RTC_AsynchPrediv �첽��Ƶ
 * @param RTC_SynchPrediv  ͬ����Ƶ
 * @param setTime          ����ʱ��Ļص� (Ĭ������Ϊ����ʱ��) (����ֵ:[1]:ʱ�������Ƿ�ɹ�, [2]:���������Ƿ�ɹ�)
 * @return uint8_t         [0]:LSE �����Ƿ�ɹ�, [1]:ʱ�������Ƿ�ɹ�, [2]:���������Ƿ�ɹ�
**/
#define NUMWRITE 0x6655  // �Ƿ����ù��ı�־ֵ
uint8_t rtcConf(uint32_t RTC_HourFormat, uint32_t AsynchPrediv, uint32_t SynchPrediv, uint8_t (*setTime)(void)) {
    RTC_InitTypeDef RTC_InitStruct;
    uint8_t temp = 0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    if (RTC_ReadBackupRegister(RTC_BKP_DR0) != NUMWRITE) {   // �Ƿ����ù�
        RCC_LSEConfig(RCC_LSE_ON);                           // LSE ����
        if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET) {      // �ȴ����پ������
            sysDelayMS(50);
            if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET)
                return 1;
        }
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);              // ѡ�� LSE ��Ϊ RTC ʱ��
        RCC_RTCCLKCmd(ENABLE);                               // ʹ�� RTC ʱ��
        RTC_InitStruct.RTC_AsynchPrediv = AsynchPrediv;      // RTC �첽��Ƶϵ�� (1~0X7F)
        RTC_InitStruct.RTC_SynchPrediv  = SynchPrediv;       // RTC ͬ����Ƶϵ�� (0~7FFF)
        RTC_InitStruct.RTC_HourFormat   = RTC_HourFormat;    // RTC ����Сʱ��ʽ
        RTC_Init(&RTC_InitStruct);
        if(setTime == _NULL_)
            setTime = setNowTime;                            // Ĭ������Ϊ��������ʱ��
        temp = setTime();
        if(temp) {
            return temp;                                     // ����ʧ��
        }
        RTC_WriteBackupRegister(RTC_BKP_DR0, NUMWRITE);      // ����Ѿ���ʼ��
    }
    return 0;
}
/**
 * @brief ��������
 *
 * @param AlarmDateWeekDaySel
 * @param AlarmDateWeekDay
 * @param AlarmHour
 * @param AlarmMinutes
 * @param AlarmSeconds
**/
void rtcAlarmConf(uint8_t AlarmHour, uint8_t AlarmMinutes, uint8_t AlarmSeconds,
                  uint8_t IsAlarmWeek, uint8_t AlarmDateWeekDay) {
    RTC_AlarmTypeDef RTC_AlarmTypeInitStruct;
    RTC_TimeTypeDef RTC_TimeTypeInitStruct;
    RTC_AlarmCmd(RTC_Alarm_A, DISABLE);                // �ر�����A
    RTC_TimeTypeInitStruct.RTC_Hours   = AlarmHour;    // Сʱ
    RTC_TimeTypeInitStruct.RTC_Minutes = AlarmMinutes; // ����
    RTC_TimeTypeInitStruct.RTC_Seconds = AlarmSeconds; // ��
    RTC_TimeTypeInitStruct.RTC_H12     = RTC_H12_AM;   // 24Сʱ��
    RTC_AlarmTypeInitStruct.RTC_AlarmTime = RTC_TimeTypeInitStruct;
    RTC_AlarmTypeInitStruct.RTC_AlarmMask = RTC_AlarmMask_None;          // ����Ϊ��, ��ȷƥ��
    if(IsAlarmWeek) {
        RTC_AlarmTypeInitStruct.RTC_AlarmDateWeekDaySel =                // �Ƿ�������
        RTC_AlarmDateWeekDaySel_WeekDay;
        RTC_AlarmTypeInitStruct.RTC_AlarmDateWeekDay = AlarmDateWeekDay; // ����
    }
    else {
        RTC_AlarmTypeInitStruct.RTC_AlarmDateWeekDaySel =
        RTC_AlarmDateWeekDaySel_Date;
    }
    RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmTypeInitStruct);
    RTC_ClearITPendingBit(RTC_IT_ALRA);   // ���RTC����A�ı�־
    RTC_ITConfig(RTC_IT_ALRA, ENABLE);    // ��������A�ж�
    RTC_AlarmCmd(RTC_Alarm_A, ENABLE);    // ��������A
}

// �����Ի��Ѷ�ʱ������
// RTC_WakeUpClock_RTCCLK_Div16
// RTC_WakeUpClock_RTCCLK_Div8
// RTC_WakeUpClock_RTCCLK_Div4
// RTC_WakeUpClock_RTCCLK_Div2
// RTC_WakeUpClock_CK_SPRE_16bits
// RTC_WakeUpClock_CK_SPRE_17bits
/**
 * @brief rtc ���ѳ�ʼ��
 *
 * @param RTC_WakeUpClock ʱ��Դѡ��
 * @param wakeCnt         �Զ���װ��ֵ
**/
void wakeConf(uint32_t RTC_WakeUpClock, uint32_t wakeCnt) {
    RTC_WakeUpCmd(DISABLE);                     // �ر� WAKE UP
    RTC_WakeUpClockConfig(RTC_WakeUpClock);     // ����ʱ��ѡ��
    RTC_SetWakeUpCounter(wakeCnt);              // ���� WAKE UP�Զ���װ�ؼĴ���
    RTC_ClearITPendingBit(RTC_IT_WUT);          // ��� RTC WAKE UP�ı�־
    EXTI_ClearITPendingBit(EXTI_Line22);        // ��� LINE22 �ϵ��жϱ�־λ
    RTC_ITConfig(RTC_IT_WUT, ENABLE);           // ���� WAKE UP ��ʱ���ж�
    RTC_WakeUpCmd(ENABLE);                      // ���� WAKE UP ��ʱ��
}

