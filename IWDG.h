#include <stdint.h>

void IWDG_init(void);
static uint32_t GetLSIFrequency(void);
bool checkIWDGstatus(void);
static void TIM16_Config(void);
