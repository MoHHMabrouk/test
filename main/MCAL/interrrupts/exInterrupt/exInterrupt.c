#include "stdTypes.h"
#include "utils.h"
#include "memMap.h"
#include "exInterrupt_interface.h"

static void (*exINT0StaticFptr)(void)=NULL_PTR;
static void (*exINT1StaticFptr)(void)=NULL_PTR;
static void (*exINT2StaticFptr)(void)=NULL_PTR;

void exInterrupt_voidEnable(exInterruptSource_t interrupt)
{
	switch(interrupt)
	{
		case EX_INT0:
		SET_BIT(GICR,INT0);
		break;
		
		case EX_INT1:
		SET_BIT(GICR,INT1);
		break;
		
		case EX_INT2:
		SET_BIT(GICR,INT2);
		break;
	}
}

void exInterrupt_voidDisable(exInterruptSource_t interrupt)
{
	switch(interrupt)
	{
		case EX_INT0:
		CLR_BIT(GICR,INT0);
		break;
		
		case EX_INT1:
		CLR_BIT(GICR,INT1);
		break;
		
		case EX_INT2:
		CLR_BIT(GICR,INT2);
		break;
	}
}

void exInterrupt_voidTriggerEdge(exInterruptSource_t interrupt,triggerEdge_t triggerEdge)
{
	switch(interrupt)
	{
		case EX_INT0:
		switch(triggerEdge)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCR,ISC00);
			break;
			
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		}
		break;


		case EX_INT1:
		switch(triggerEdge)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
		}
		break;

		case EX_INT2:
		switch(triggerEdge)
		{
			case FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;
			default:
			CLR_BIT(MCUCSR,ISC2);
		}
		break;
	}
}

void exInterrupt_voidSetCallBack(exInterruptSource_t interrupt,void (*localPtr)(void))
{
	switch(interrupt)
	{
		case EX_INT0:
		exINT0StaticFptr=localPtr;
		break;
		
		case EX_INT1:
		exINT1StaticFptr=localPtr;
		break;
		
		case EX_INT2:
		exINT2StaticFptr=localPtr;
		break;
	}
}

ISR(INT0_vect)
{
	if(exINT0StaticFptr!=NULL_PTR)
	{
		exINT0StaticFptr();
	}
}

ISR(INT1_vect)
{
	if(exINT1StaticFptr!=NULL_PTR)
	{
		exINT1StaticFptr();
	}
}

ISR(INT2_vect)
{
	if(exINT2StaticFptr!=NULL_PTR)
	{
		exINT2StaticFptr();
	}
}