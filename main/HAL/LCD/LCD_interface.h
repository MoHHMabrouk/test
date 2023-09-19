#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


void LCD_voidInit(void);

void LCD_voidGoTo(u8 line,u8 cell);

void LCD_voidWriteChar(u8 ch);

void LCD_voidWriteString(c8*str);

void LCD_voidWriteNumber(u32 num);

void LCD_voidWriteBinary(u8 num);

#endif /* LCD_INTERFACE_H_ */