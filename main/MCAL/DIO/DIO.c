#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_cfg.h"
#include "stdTypes.h"
#include "utils.h"
#include "memMap.h"


void DIO_voidInit(void)
{
	for(DIO_pinType pin=PINA0;pin<TOTAL_PINS;pin++)
	{
		DIO_initPin(pin,DIO_pinStatusArray[pin]);
	}
}

static void DIO_initPin(DIO_pinType pin,DIO_pinStatusType status)
{
	DIO_portType port=pin/8;
	u8 pinNum=pin%8;
	pu8 pDDR,pPORT;
	
	switch(port)
	{
		case PA:
		pDDR=&DDRA;
		pPORT=&PORTA;
		break;
		
		case PB:
		pDDR=&DDRB;
		pPORT=&PORTB;
		break;
		
		case PC:
		pDDR=&DDRC;
		pPORT=&PORTC;
		break;
		
		case PD:
		pDDR=&DDRD;
		pPORT=&PORTD;
		break;
	}
	
	switch(status)
	{
		case OUTPUT:
		SET_BIT((*pDDR),pinNum);
		CLR_BIT((*pPORT),pinNum);
		break;
		
		case INPULL:
		CLR_BIT((*pDDR),pinNum);
		SET_BIT((*pPORT),pinNum);
		break;
		
		case INFREE:
		CLR_BIT((*pDDR),pinNum);
		CLR_BIT((*pPORT),pinNum);
		break;
	}
}

void DIO_writePin(DIO_pinType pin,DIO_pinVoltageType pinVolt)
{
	DIO_portType port=pin/8;
	u8 pinNum=pin%8;
	
	if(pinVolt==HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA,pinNum);
			break;
			
			case PB:
			SET_BIT(PORTB,pinNum);
			break;
			
			case PC:
			SET_BIT(PORTC,pinNum);
			break;
			
			case PD:
			SET_BIT(PORTD,pinNum);
			break;
		}
	}
	else
	{
		switch(port)
		{
			case PA:
			CLR_BIT(PORTA,pinNum);
			break;
			
			case PB:
			CLR_BIT(PORTB,pinNum);
			break;
			
			case PC:
			CLR_BIT(PORTC,pinNum);
			break;
			
			case PD:
			CLR_BIT(PORTD,pinNum);
			break;
		}
	}
}

DIO_pinVoltageType DIO_readPin(DIO_pinType pin)
{
	DIO_portType port=pin/8;
	u8 pinNum=pin%8;
	DIO_pinVoltageType volt=LOW;
	
	switch(port)
	{
		case PA:
		volt=READ_BIT(PINA,pinNum);
		break;
		
		case PB:
		volt=READ_BIT(PINB,pinNum);
		break;
		
		case PC:
		volt=READ_BIT(PINC,pinNum);
		break;
		
		case PD:
		volt=READ_BIT(PIND,pinNum);
		break;
	}
	return volt;
}

void DIO_togglePin(DIO_pinType pin)
{
	DIO_portType port=pin/8;
	u8 pinNum=pin%8;
	
	switch (port)
	{
		case PA:
		TOG_BIT(PORTA,pinNum);
		break;
		
		case PB:
		TOG_BIT(PORTB,pinNum);
		break;
		
		case PC:
		TOG_BIT(PORTC,pinNum);
		break;
		
		case PD:
		TOG_BIT(PORTD,pinNum);
		break;
	}
}


void DIO_writePort(DIO_portType port,u8 data)
{
	switch(port)
	{
		case PA:
		PORTA=data;
		break;
		
		case PB:
		PORTB=data;
		break;
		
		case PC:
		PORTC=data;
		break;
		
		case PD:
		PORTD=data;
		break;
	}
}
/*******************************************************************/

