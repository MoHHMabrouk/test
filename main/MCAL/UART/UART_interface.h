#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
#include "stdTypes.h"
#include "memMap.h"
#include "utils.h"
typedef enum
{
	NO_DATA,
	RECIEVED
}UART_recieverData_t;

void UART_voidInit(void);

void UART_voidSendChar(u8 data);

UART_recieverData_t UARTRecievePeriodic(u8*pData);

#endif /* UART_INTERFACE_H_ */