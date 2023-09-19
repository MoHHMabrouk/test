#include "UART_interface.h"

void UART_voidInit(void)
{
	/* Setting Baud Rate */
	UBRRL=103;
	
	
	/* Setting Speed */
	//CLEAR_BIT(UCSRA,U2X); // Normal Speed
	
	/* Setting Frame Format : Data bits - Parity bit type - Number of stop bits */
	/* Data bits = 8 bits - No Parity - Number of stop bits = 1 */
	//Default
	
	/* Enable RX TX */
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
}

void UART_voidSendChar(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}

UART_recieverData_t UARTRecievePeriodic(u8*pData)
{

	if(READ_BIT(UCSRA,RXC))
	{
		*pData=UDR;
		return RECIEVED;
	}
	
	return NO_DATA;
	
}