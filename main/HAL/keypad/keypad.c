#define F_CPU 16000000

#include <util/delay.h>
#define KEYPAD 1

#include "DIO_interface.h"
#include "keypad_interface.h"


#include "keypad_cfg.h"



void KEYPAD_voidInit(void)
{
	for(u8 r=0;r<ROWS;r++)
	{
		DIO_writePin(FIRST_OUT+r,HIGH);
	}
}

void KEYPAD_voidGetKey(u8 *localKeyPtr)
{
	u8 r,c,key=NO_KEY;
	for(r=0;r<ROWS;r++)
	{
		DIO_writePin(FIRST_OUT+r,LOW);
		for(c=0;c<COLS;c++)
		{
			if(DIO_readPin(FIRST_IN+c)==0)
			{
				key=keys[r][c];
				_delay_ms(10);
				while(DIO_readPin(FIRST_IN+c)==0);
				_delay_ms(10);
			}
			
		}
		DIO_writePin(FIRST_OUT+r,HIGH);
	}
	*localKeyPtr=key;
}