#include <stm32f30x_flash.h>
#define FLASH_PAGE_SIZE         ((uint32_t)0x00000800)   /* FLASH Page Size */
#define FLASH_USER_START_ADDR   ((uint32_t)0x08006000)   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ((uint32_t)0x08007000)   /* End @ of user Flash area */
#define DATA_32                 ((uint32_t)0x12345678)

void flashData()
{
	uint32_t EraseCounter = 0x00, Address = 0x00;
	uint32_t Data = 0x3210ABCD;
	uint32_t NbrOfPage = 0x00;

	/* Unlock the Flash to enable the flash control register access *************/
	FLASH_Unlock();

	/* Erase the user Flash area
	(area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	/* Clear pending flags (if any) */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

	/* Define the number of page to be erased */
	NbrOfPage = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / FLASH_PAGE_SIZE;

	/* Erase the FLASH pages */
	for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASH_GetStatus() == FLASH_COMPLETE); EraseCounter++)
	{
		if (FLASH_ErasePage(FLASH_USER_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter)) != FLASH_COMPLETE)
		{
			/* Error occurred while sector erase.
			User can add here some code to deal with this error  */
			while (1)
			{
			}
		}
	}
	/* Program the user Flash area word by word
	(area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	Address = FLASH_USER_START_ADDR;

	while (Address < FLASH_USER_END_ADDR)
	{
		if (FLASH_ProgramWord(Address, DATA_32) == FLASH_COMPLETE)
		{
			Address = Address + 4;
		}
		else
		{
			/* Error occurred while writing data in Flash memory.
			User can add here some code to deal with this error */
			while (1)
			{
			}
		}
	}

	/* Lock the Flash to disable the flash control register access (recommended
	to protect the FLASH memory against possible unwanted operation) *********/
	FLASH_Lock();
}
