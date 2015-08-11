#include <stm32f30x_wwdg.h>
#include <stm32f30x_rcc.h>

void setWDT()
{
/* WWDG configuration */
  /* Enable WWDG clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	  /* WWDG clock counter = (PCLK1 (36MHz)/4096)/8 = 1098Hz (~910 us)  */
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	  /* Set Window value to 80; WWDG counter should be refreshed only when the counter
	    is below 80 (and greater than 64) otherwise a reset will be generated */
	WWDG_SetWindowValue(80);
	  /* Enable WWDG and set counter value to 127, WWDG timeout = ~910 us * 64 = 58.24 ms 
	    In this case the refresh window is: ~910 * (127-80) = 42.7ms < refresh window < ~910 * 64 = 58.2ms
	  */
	WWDG_Enable(127);
}

extern "C" void WWDG_IRQHandler(void)
{
	
}
