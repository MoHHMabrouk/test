#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#include "LCD_Private.h"

/******************* 4 Bit or 8 Bit Mode *******************/
#define LCD_MODE _4_BIT_

#define RS PINA3
#define EN PINA2

/******************* 4 Bit Mode only *******************/
#define D4 PINB0
#define D5 PINB1
#define D6 PINB2
#define D7 PINB4

/******************* 8 Bit Mode only *******************/
#define LCD_PORT PB

#endif /* LCD_CFG_H_ */