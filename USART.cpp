#include <stm32f30x.h>
#include <stm32f30x_usart.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>

#define BUF_MAX_SIZE 256

static char Recv1Buff[BUF_MAX_SIZE];
static int Recv1Pointer = 0;
static char Recv2Buff[BUF_MAX_SIZE];
static int Recv2Pointer = 0;
static char Recv3Buff[BUF_MAX_SIZE];
static int Recv3Pointer = 0;

void USART1_Init()
{
	USART_TypeDef USART1_InitType;
	USART_InitTypeDef USART1_InitStructure;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;	// Enable USART clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_AHBPeriph_GPIOA, ENABLE);
	USART1_InitStructure.USART_BaudRate = 115200;
	USART1_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART1_InitStructure.USART_StopBits = USART_StopBits_1;
	USART1_InitStructure.USART_Parity = USART_Parity_No;
	USART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// Configure the USART1
	USART_Init(USART1, &USART1_InitStructure);
	// Enable USART1 interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	// Enable the USART1
	USART_Cmd(USART1, ENABLE);
	// Enable USART1 global interrupt
	NVIC_EnableIRQ(USART1_IRQn);
	GPIO_InitTypeDef GPIO_InitStructure;

    //PA2 = USART1.TX => Alternative Function Output
	//PA3 = USART1.RX => Input
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// Connect PA2 and PA3 with the USART2 Alternate Function
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
}

void USART2_Init()
{
	USART_TypeDef USART2_InitType;
	USART_InitTypeDef USART2_InitStructure;
	USART2_InitStructure.USART_BaudRate = 115200;
	USART2_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART2_InitStructure.USART_StopBits = USART_StopBits_1;
	USART2_InitStructure.USART_Parity = USART_Parity_No;
	USART2_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART2_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// Configure the USART2
	USART_Init(USART2, &USART2_InitStructure);
	// Enable USART2 interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	// Enable the USART2
	USART_Cmd(USART2, ENABLE);
	// Enable USART2 global interrupt
	NVIC_EnableIRQ(USART2_IRQn);
}

void USART3_Init()
{
	USART_TypeDef USART3_InitType;
	USART_InitTypeDef USART3_InitStructure;
	USART3_InitStructure.USART_BaudRate = 115200;
	USART3_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART3_InitStructure.USART_StopBits = USART_StopBits_1;
	USART3_InitStructure.USART_Parity = USART_Parity_No;
	USART3_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART3_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// Configure the USART3
	USART_Init(USART3, &USART3_InitStructure);
	// Enable USART3 interrupt
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	// Enable the USART3
	USART_Cmd(USART3, ENABLE);
	// Enable USART3 global interrupt
	NVIC_EnableIRQ(USART3_IRQn);
}

extern "C" void USART1_IRQHandler(void)
{
	// RXNE handler
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Recv1Buff[Recv1Pointer] = (char) USART_ReceiveData(USART1);
		USART_SendData(USART1, Recv1Buff[Recv1Pointer]);
		Recv1Pointer++;
		if (Recv1Pointer > (BUF_MAX_SIZE - 1))
			Recv1Pointer = 0;
	}
	return;
}

extern "C" void USART2_IRQHandler(void)
{
	// RXNE handler
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Recv2Buff[Recv2Pointer] = (char) USART_ReceiveData(USART2);
		USART_SendData(USART2, Recv2Buff[Recv2Pointer]);
		Recv2Pointer++;
		if (Recv2Pointer > (BUF_MAX_SIZE - 1))
			Recv2Pointer = 0;
	}
	return;
}

extern "C" void USART3_IRQHandler(void)
{
	// RXNE handler
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		Recv3Buff[Recv3Pointer] = (char) USART_ReceiveData(USART3);
		USART_SendData(USART3, Recv3Buff[Recv3Pointer]);
		Recv3Pointer++;
		if (Recv3Pointer > (BUF_MAX_SIZE - 1))
			Recv3Pointer = 0;
	}
	return;
}

void USART_SendChar(USART_TypeDef* sUSARTx, char ch)
{
	USART_SendData(sUSARTx, (uint8_t) ch);
	/* Loop until transmit data register is empty */
	while (USART_GetFlagStatus(sUSARTx, USART_FLAG_TXE) == RESET) {}
}
