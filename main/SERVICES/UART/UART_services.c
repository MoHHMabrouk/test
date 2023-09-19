#include "UART_interface.h"

void UARTSendString(c8*dataString)
{
	for(u8 charsCounter=0;dataString[charsCounter];charsCounter++)
	{
		UART_voidSendChar(dataString[charsCounter]);
	}
}