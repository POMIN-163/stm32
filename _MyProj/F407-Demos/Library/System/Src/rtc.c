#include "rtc.h"

/**
 * @brief 读取日期和时间
 *
 * @param rtcTime 时间结构体指针
 * @param rtcDate 日期结构体指针
**/
void rtcGetTime(RTC_TimeTypeDef *rtcTime, RTC_DateTypeDef *rtcDate) {
    RTC_GetDate(RTC_Format_BIN, rtcDate);
    RTC_GetTime(RTC_Format_BIN, rtcTime);
}
/**
 * @brief 设置为编译时间
 *
 * @return uint8_t [1]:时间设置是否成功, [2]:日期设置是否成功
**/
uint8_t setNowTime(void) {
    char strDate[20];                  // 日期字符串
    char strTime[20];                  // 时间字符串
    int32_t year, mouth, date;         // 日期参数
    RTC_TimeTypeDef nowTime;
    RTC_DateTypeDef nowDate;
    sprintf(strDate, "%s", __DATE__);  // 格式化日期 xxx xx xxxx
    sprintf(strTime, "%s", __TIME__);  // 格式化时间 xx:xx:xx
    strDate[3] = '\0';                 // 分割日期
    strDate[6] = '\0';
    strTime[2] = '\0';                 // 分割时间
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
    else                                  nowDate.RTC_Month = mouth = 1;   // 获取月份 (1~12)
    year = atoi(strDate + 4 + 3);
    nowDate.RTC_Year    = year - 2000;                                     // 获取年份 (0~99)
    nowDate.RTC_Date    = date = atoi(strDate + 4);                        // 获取日期 (0~31)
    if(mouth == 1 || mouth == 2) {
        mouth += 12; year--;                                               // 基姆拉尔森公式
    }
    nowDate.RTC_WeekDay =                                                  // 获取星期 (1~7)
        (date + 2 * mouth + 3 * (mouth + 1) / 5 + year + year / 4 - year / 100 +
         year / 400) % 7 + 1;
    nowTime.RTC_Hours   = atoi(strTime);                                   // 获取时间
    nowTime.RTC_Minutes = atoi(strTime + 3);
    nowTime.RTC_Seconds = atoi(strTime + 6);
    nowTime.RTC_H12     = RTC_H12_AM;                                      // 24 小时制
    return ((uint8_t)!RTC_SetDate(RTC_Format_BIN, &nowDate) << 2) |
           ((uint8_t)!RTC_SetTime(RTC_Format_BIN, &nowTime) << 1);
}
/**
 * @brief 初始化 RTC 时钟
 *
 * @param RTC_HourFormat   日期格式
 * @param RTC_AsynchPrediv 异步分频
 * @param RTC_SynchPrediv  同步分频
 * @param setTime          设置时间的回调 (默认设置为编译时间) (返回值:[1]:时间设置是否成功, [2]:日期设置是否成功)
 * @return uint8_t         [0]:LSE 开启是否成功, [1]:时间设置是否成功, [2]:日期设置是否成功
**/
#define NUMWRITE 0x6655  // 是否配置过的标志值
uint8_t rtcConf(uint32_t RTC_HourFormat, uint32_t AsynchPrediv, uint32_t SynchPrediv, uint8_t (*setTime)(void)) {
    RTC_InitTypeDef RTC_InitStruct;
    uint8_t temp = 0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    if (RTC_ReadBackupRegister(RTC_BKP_DR0) != NUMWRITE) {   // 是否配置过
        RCC_LSEConfig(RCC_LSE_ON);                           // LSE 开启
        if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET) {      // 等待低速晶振就绪
            sysDelayMS(50);
            if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET)
                return 1;
        }
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);              // 选择 LSE 作为 RTC 时钟
        RCC_RTCCLKCmd(ENABLE);                               // 使能 RTC 时钟
        RTC_InitStruct.RTC_AsynchPrediv = AsynchPrediv;      // RTC 异步分频系数 (1~0X7F)
        RTC_InitStruct.RTC_SynchPrediv  = SynchPrediv;       // RTC 同步分频系数 (0~7FFF)
        RTC_InitStruct.RTC_HourFormat   = RTC_HourFormat;    // RTC 设置小时格式
        RTC_Init(&RTC_InitStruct);
        if(setTime == _NULL_)
            setTime = setNowTime;                            // 默认设置为代码编译的时间
        temp = setTime();
        if(temp) {
            return temp;                                     // 设置失败
        }
        RTC_WriteBackupRegister(RTC_BKP_DR0, NUMWRITE);      // 标记已经初始化
    }
    return 0;
}
/**
 * @brief 闹钟配置
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
    RTC_AlarmCmd(RTC_Alarm_A, DISABLE);                // 关闭闹钟A
    RTC_TimeTypeInitStruct.RTC_Hours   = AlarmHour;    // 小时
    RTC_TimeTypeInitStruct.RTC_Minutes = AlarmMinutes; // 分钟
    RTC_TimeTypeInitStruct.RTC_Seconds = AlarmSeconds; // 秒
    RTC_TimeTypeInitStruct.RTC_H12     = RTC_H12_AM;   // 24小时制
    RTC_AlarmTypeInitStruct.RTC_AlarmTime = RTC_TimeTypeInitStruct;
    RTC_AlarmTypeInitStruct.RTC_AlarmMask = RTC_AlarmMask_None;          // 掩码为空, 精确匹配
    if(IsAlarmWeek) {
        RTC_AlarmTypeInitStruct.RTC_AlarmDateWeekDaySel =                // 是否安星期闹
        RTC_AlarmDateWeekDaySel_WeekDay;
        RTC_AlarmTypeInitStruct.RTC_AlarmDateWeekDay = AlarmDateWeekDay; // 星期
    }
    else {
        RTC_AlarmTypeInitStruct.RTC_AlarmDateWeekDaySel =
        RTC_AlarmDateWeekDaySel_Date;
    }
    RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmTypeInitStruct);
    RTC_ClearITPendingBit(RTC_IT_ALRA);   // 清除RTC闹钟A的标志
    RTC_ITConfig(RTC_IT_ALRA, ENABLE);    // 开启闹钟A中断
    RTC_AlarmCmd(RTC_Alarm_A, ENABLE);    // 开启闹钟A
}

// 周期性唤醒定时器设置
// RTC_WakeUpClock_RTCCLK_Div16
// RTC_WakeUpClock_RTCCLK_Div8
// RTC_WakeUpClock_RTCCLK_Div4
// RTC_WakeUpClock_RTCCLK_Div2
// RTC_WakeUpClock_CK_SPRE_16bits
// RTC_WakeUpClock_CK_SPRE_17bits
/**
 * @brief rtc 唤醒初始化
 *
 * @param RTC_WakeUpClock 时钟源选择
 * @param wakeCnt         自动重装载值
**/
void wakeConf(uint32_t RTC_WakeUpClock, uint32_t wakeCnt) {
    RTC_WakeUpCmd(DISABLE);                     // 关闭 WAKE UP
    RTC_WakeUpClockConfig(RTC_WakeUpClock);     // 唤醒时钟选择
    RTC_SetWakeUpCounter(wakeCnt);              // 设置 WAKE UP自动重装载寄存器
    RTC_ClearITPendingBit(RTC_IT_WUT);          // 清除 RTC WAKE UP的标志
    EXTI_ClearITPendingBit(EXTI_Line22);        // 清除 LINE22 上的中断标志位
    RTC_ITConfig(RTC_IT_WUT, ENABLE);           // 开启 WAKE UP 定时器中断
    RTC_WakeUpCmd(ENABLE);                      // 开启 WAKE UP 定时器
}

