#include <stm32f30x_rcc.h>

void SetRCC()
{

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // GPIOA Clock Enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE); // GPIOB Clock Enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE); // GPIOC Clock Enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE); // GPIOE Clock Enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable TIM2 clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); // Enable PWR clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // Enable the SYSCFG APB clock to get write access to comparator register and EXTI line interrupts
}
