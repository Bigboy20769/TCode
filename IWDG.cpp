#include <stm32f30x.h>
#include <stm32f30x_iwdg.h>
#include <stm32f30x_tim.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_pwr.h>
#include <stm32f30x_misc.h>
#include "IWDG.h"
#define STM32F303xB true

void IWDG_init()
{
	__IO uint32_t uwLsiFreq = 0;

	uwLsiFreq = GetLSIFrequency();

	/* Set counter reload value to obtain 250ms IWDG TimeOut.
	IWDG counter clock Frequency = LsiFreq/32
	Counter Reload Value = 250ms/IWDG counter clock period
	= 0.25s / (32/LsiFreq)
	= LsiFreq/(32 * 4)
	= LsiFreq/128 */
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	/* Set counter reload value to obtain 250ms IWDG TimeOut.
	Counter Reload Value = 250ms * IWDG counter clock period
	= 250ms * (LSI/32)
	= 0.25s * (LsiFreq/32)
	= LsiFreq / (32 * 4)
	= LsiFreq / 128
	*/
	IWDG_SetReload(uwLsiFreq / 128);
	/* Reload IWDG counter */
	IWDG_ReloadCounter();

	/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	IWDG_Enable();
	/* Enable write access to IWDG_PR and IWDG_RLR registers */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
}

static uint32_t GetLSIFrequency(void)
{

	/* Wait until the TIM16 get 2 LSI edges (refer to TIM16_IRQHandler() in
	stm32f3xx_it.c file) ******************************************************/
//	while (uwCaptureNumber != 2)
	{
	}

	/* Disable TIM16 CC1 Interrupt Request */
//	TIM_IC_Stop_IT(&Input_Handle, TIM_CHANNEL_1);

	/* Deinitialize the TIM16 peripheral registers to their default reset values */
//	TIM_IC_DeInit(&Input_Handle);

//	return uwLsiFreq/*0*/;
}

bool checkIWDGstatus()
{
	/* Check if the system has resumed from IWDG reset */
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		/* IWDGRST flag set */
		/* Clear reset flags */
		RCC_ClearFlag();
		return(true);
	}
	else
	{
		/* IWDGRST flag is not set */
		return(false);
	}
}

static void TIM16_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	/* Enable peripheral clocks ------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* Allow access to the RTC */
	PWR_BackupAccessCmd(ENABLE);

	/* Reset RTC Domain */
	RCC_BackupResetCmd(ENABLE);
	RCC_BackupResetCmd(DISABLE);

	/*!< LSI Enable */
	RCC_LSICmd(ENABLE);

	/*!< Wait till LSI is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{
	}

	/* Enable TIM16 clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);

	/* Enable the TIM16 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM16_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Configure TIM16 prescaler */
	TIM_PrescalerConfig(TIM16, 0, TIM_PSCReloadMode_Immediate);

	/* Connect internally the TM16_CH1 Input Capture to the LSI clock output */
	//  TIM_RemapConfig(TIM16, TIM16_RTC_CLK);
	TIM16->OR = 0x3;
	RCC_MCOConfig(RCC_MCOSource_LSI, RCC_MCOPrescaler_1);
	/* TIM16 configuration: Input Capture mode ---------------------
	The LSI oscillator is connected to TIM16 CH1
	The Rising edge is used as active edge,
	The TIM16 CCR1 is used to compute the frequency value
	------------------------------------------------------------ */
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV8;
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM16, &TIM_ICInitStructure);

	/* TIM16 Counter Enable */
	TIM_Cmd(TIM16, ENABLE);

	/* Reset the flags */
	TIM16->SR = 0;

	/* Enable the CC1 Interrupt Request */
	TIM_ITConfig(TIM16, TIM_IT_CC1, ENABLE);
}
