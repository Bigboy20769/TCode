#include <stm32f30x_rtc.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_pwr.h>
#include <stm32f30x_exti.h>
#include <stm32f30x_gpio.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "RTC.h"

RTC_TimeTypeDef		RTC_TimeStructure;
RTC_DateTypeDef		RTC_DateStructure;
RTC_InitTypeDef		RTC_InitStructure;
RTC_AlarmTypeDef	RTC_AlarmStructure;

char showtime[50] = { 0 };
char showdate[50] = { 0 };
char showdatetime[50] = { 0 };

void RTC_SetUp(void)
{
  /* Allow access to RTC */
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSICmd(ENABLE); // LSI is used as RTC clock source
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
		; // Wait till LSI is ready

	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI); // Select RTC clock source
// Enable RTC clock
	RCC_RTCCLKCmd(ENABLE);

	RTC_WaitForSynchro(); // Wait until the RTC Time and Date registers (RTC_TR and RTC_DR) are synchronized with RTC APB clock.

	  // Set RTC calendar clock to 1 HZ (1 second)
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	RTC_InitStructure.RTC_AsynchPrediv = 88;
	RTC_InitStructure.RTC_SynchPrediv = 470;
  
	if (RTC_Init(&RTC_InitStructure) == ERROR)
	{
		while (1)
			;
	}
}

void SetRTC_Time(void)
{
		// Set the time to 01h 00mn 00s AM 
	RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
	RTC_TimeStructure.RTC_Hours   = 0x01;
	RTC_TimeStructure.RTC_Minutes = 0x00;
	RTC_TimeStructure.RTC_Seconds = 0x00;  

	RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure); // Write values to registers
}

void SetRTC_AlarmTime(void)
{
	/* Set the alarm to current time + 5s */
	RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = RTC_TimeStructure.RTC_Hours;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = RTC_TimeStructure.RTC_Minutes;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = RTC_TimeStructure.RTC_Seconds + 10;
	RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay | RTC_AlarmMask_Minutes | RTC_AlarmMask_Hours;
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);

	// Enable the RTC Alarm A interrupt
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);

	// Enable the alarm
	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);

	// Clear the Alarm A Pending Bit
	RTC_ClearITPendingBit(RTC_IT_ALRA);
}

char* GetRTCTime(void)
{
	/* Get the RTC current Time */
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	/* Get the RTC current Date */
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	/* Display time Format : hh:mm:ss */
	sprintf(showtime, "%.2d:%.2d:%.2d", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
	return(showtime);
}

char* GetRTCDate(void)
{
	/* Get the RTC current Time */
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	/* Get the RTC current Date */
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	/* Display date Format : mm-dd-yy */
	sprintf(showdate, "%.2d-%.2d-%.2d", RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date, 2000 + RTC_DateStructure.RTC_Year);   
	return(showdate);
}

char* GetRTCDateTime(void)
{
	    /* Get the RTC current Time */
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	/* Get the RTC current Date */
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	/* Display time Format : hh:mm:ss */
	sprintf((char*)showtime, "%.2d:%.2d:%.2d", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
	/* Display date Format : mm-dd-yy */
	sprintf(showdate, "%.2d-%.2d-%.2d", RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date, 2000 + RTC_DateStructure.RTC_Year);   
	strcat(showdatetime, showdate);
	strcat(showdatetime, "  ");
	strcat(showdatetime, showtime);
	return(showdatetime);
}

extern "C" void RTC_Alarm_IRQHandler(void)
{
	/* RTC Alarm A check */
	if (RTC_GetITStatus(RTC_IT_ALRA) != RESET) {
		/* Clear RTC Alarm A interrupt flag */
		RTC_ClearITPendingBit(RTC_IT_ALRA);
		/* Call user function for Alarm A */
		RTC_AlarmA_function();
	}
	/* RTC Alarm B check */
	if (RTC_GetITStatus(RTC_IT_ALRB) != RESET) {
		/* Clear RTC Alarm A interrupt flag */
		RTC_ClearITPendingBit(RTC_IT_ALRB);
		/* Call user function for Alarm B */
		RTC_AlarmB_function();
	}
	/* Clear EXTI line 17 bit */
	EXTI->PR = 0x00020000;
}

void RTC_AlarmA_function()
{
	return;
}

void RTC_AlarmB_function()
{
	return;
}

extern "C" void RTC_WKUP_IRQHandler(void)
{
	
}