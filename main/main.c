#define F_CPU 16000000

#include <util/delay.h>
#include "DIO_interface.h"
#include "stdTypes.h"
#include "LCD_interface.h"
#include "Timer_interface.h"
/*#include "Servo_interface.h"*/
#include "memMap.h"
#include "ADC_interface.h"
/*#include "Sensors_interface.h"*/
#include "exInterrupt_interface.h"
#include "UART_interface.h"
#include "keypad_interface.h"
#include "UART_services.h"
#include "exInterrupt_service_interface.h"


int main(void)
{
	DIO_voidInit();
	LCD_voidInit();
	PWM_exInterruptInit();
	LCD_voidGoTo(0,0);
	LCD_voidWriteString("Duty:");
	LCD_voidGoTo(1,0);
	LCD_voidWriteString("Freq:");
	GLOBALINT_voidEnable();

	while(1)
	{

	}
}
