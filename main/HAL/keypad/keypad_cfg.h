#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#include "DIO_interface.h"
#include "stdTypes.h"

#define ROWS 4
#define COLS 4

#define FIRST_OUT PINC2
#define FIRST_IN PIND3

#define	NO_KEY	'T'



#if KEYPAD
u8 keys[ROWS][COLS]={{'7','8','9','/'}
,{'4','5','6','*'}
,{'1','2','3','-'}
,{'C','0','=','+'}};

#endif





#endif /* KEYPAD_CFG_H_ */