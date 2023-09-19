#include "Timer_interface.h"
#include "memMap.h"

void SERVO_voidInit(void)
{
	TIMER1_voidInit(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_preScaler_8);
	TIMER1_voidOCRB1Mode(OCRB_NON_INVERTING);
	OCR1A=19999;
	OCR1B=499;
}

void SERVO_voidAngle(u8 angle)
{
	if(angle>180)
	{
		angle=180;
	}
	OCR1B=(((angle*(u32)2000))/(u32)180)+499;	
}