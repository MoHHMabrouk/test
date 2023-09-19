#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "stdTypes.h"

typedef enum{
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}DIO_pinType;

typedef enum{
	OUTPUT,
	INFREE,
	INPULL
}DIO_pinStatusType;

typedef enum{
	PA=0,
	PB,
	PC,
	PD
}DIO_portType;


typedef enum{
	LOW,
	HIGH
}DIO_pinVoltageType;



void DIO_voidInit(void);

void DIO_writePin(DIO_pinType pin,DIO_pinVoltageType pinVolt);

DIO_pinVoltageType DIO_readPin(DIO_pinType pin);

void DIO_togglePin(DIO_pinType pin);

void DIO_writePort(DIO_portType port,u8 data);



#endif /* DIO_INTERFACE_H_ */