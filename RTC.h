void RTC_SetUp(void);
void SetRTC_Time(void);
void SetRTC_AlarmTime(void);
char * GetRTCTime(void);
char * GetRTCDate(void);
char * GetRTCDateTime(void);
extern "C" void RTC_Alarm_IRQHandler(void);
/* Callbacks */
void RTC_AlarmA_function(void);
void RTC_AlarmB_function(void);
