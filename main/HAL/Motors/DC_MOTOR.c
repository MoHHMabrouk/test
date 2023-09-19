#include "DC_MOTOR_interface.h"
#include "Timer_interface.h"


void DC_MOTOR_voidSpeedControl(DC_MOTOR_speed_t speed)
{
	switch(speed)
	{
		case LEVEL_1_SPEED:
		TIMER0_voidSetOCR0(51);
		break;
		
		case LEVEL_2_SPEED:
		TIMER0_voidSetOCR0(102);
		break;
		
		case LEVEL_3_SPEED:
		TIMER0_voidSetOCR0(154);
		break;
		
		case LEVEL_4_SPEED:
		TIMER0_voidSetOCR0(205);
		break;
		
		case LEVEL_5_SPEED:
		TIMER0_voidSetOCR0(255);
		break;
		
	}
}