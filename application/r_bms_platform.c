#include "bms_user_firmware_example.h"

/*******************************************************************************
* Function Name: Stop_Mode
* Description  : Executes Stop_Mode routine in the BMS module.
* Arguments    : None
* Return Value : None
* Notes        : Auto-generated API comment block for maintainability.
*******************************************************************************/
void Stop_Mode(void)
{
	DI();
	if(BMS_Event_HasPending())
	{
		EI();
		return;
	}
	WUP0 = 1;
	NOP();										// wait 3clock
	NOP();
	NOP();
	EI();									// Interrupt enable
	STOP();								// Stop mode
	NOP();							// wait 5clock
	NOP();
	NOP();
	NOP();
	NOP();
	WUP0 = 0;
}
