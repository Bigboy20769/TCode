#include <stm32f30x_rcc.h>
#include <stm32f30x_adc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_misc.h>
#include "Systick.h"

void ADC_WDG_init()
{
	uint16_t calibration_value = 0;
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the ADC clock */
	RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div128);
	/* Enable ADC1 clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
	/* ADC Channel configuration */
	/* GPIOC Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	/* Configure ADC Channel7 as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	ADC_StructInit(&ADC_InitStructure);
	/* Calibration procedure */ 
	ADC_VoltageRegulatorCmd(ADC1, ENABLE);
	/* Insert delay equal to 10 µs */
//	Delay(10);
	ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC1);
  
	while (ADC_GetCalibrationStatus(ADC1) != RESET)
		;
	calibration_value = ADC_GetCalibrationValue(ADC1);
     
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;
	ADC_CommonInit(ADC1, &ADC_CommonInitStructure);
  
	ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
	ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Enable;
	ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	ADC_InitStructure.ADC_NbrOfRegChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
  
	/* ADC1 regular channel7 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_7Cycles5);
	/* Analog watchdog 2 configuration */
	/* Configure channel7 as the single analog watchdog guarded channel */
	ADC_AnalogWatchdog2SingleChannelConfig(ADC1, ADC_Channel_7);
	/* Configure the ADC Thresholds between 1.5V and 0.8V */
	ADC_AnalogWatchdog2ThresholdsConfig(ADC1, 0x7F, 0x3F);
  
	/* Configure and enable ADC1 interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable AWD interrupt */
	ADC_ITConfig(ADC1, ADC_IT_AWD2, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/* wait for ADRDY */
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY))
		;
	/* Start ADC1 Software Conversion */
	ADC_StartConversion(ADC1);
}

uint16_t getADC_Conversion(void)
{
	uint16_t ADC1ConvertedValue = 0;
	uint16_t ADC1ConvertedVoltage = 0;

	ADC1ConvertedValue = ADC_GetConversionValue(ADC1);
	/* Compute the voltage */
	ADC1ConvertedVoltage = (ADC1ConvertedValue * 3300) / 0xFFF;
	return ADC1ConvertedVoltage;
}

extern "C" void ADC1_2_IRQHandler(void)
{
	if (ADC_GetITStatus(ADC1, ADC_IT_AWD1))
	{
		ADC_ClearITPendingBit(ADC1, ADC_IT_AWD1);
	}
}
