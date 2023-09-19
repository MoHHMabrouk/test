#define F_CPU 16000000

#include <util/delay.h>
#include "DIO_interface.h"
#include "keypad_interface.h"
#include "LCD_interface.h"

void calc_voidInit(void)
{
	DIO_voidInit();
	LCD_voidInit();
	KEYPAD_voidInit();
}


void calc_voidRunnable(void)
{
	
	

	
}