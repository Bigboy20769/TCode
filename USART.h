void USART1_Init();
void USART2_Init();
void USART3_Init();
extern "C" void USART1_IRQHandler(void);
extern "C" void USART2_IRQHandler(void);
extern "C" void USART3_IRQHandler(void);
void USART_SendChar(USART_TypeDef *sUARTx, char data);
