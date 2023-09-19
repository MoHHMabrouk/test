#define F_CPU	16000000
#include <util/delay.h>

#include "stdTypes.h"
#include "DIO_interface.h"
#include "DIO_cfg.h"
#include "LCD_cfg.h"
#include "utils.h"

static u8 line_Counter;
static u8 flag;

#if LCD_MODE==_4_BIT_
static void WriteIns(u8 ins)
{
	DIO_writePin(RS,LOW);
	DIO_writePin(D7,READ_BIT(ins,7));
	DIO_writePin(D6,READ_BIT(ins,6));
	DIO_writePin(D5,READ_BIT(ins,5));
	DIO_writePin(D4,READ_BIT(ins,4));
	DIO_writePin(EN,HIGH);
	_delay_ms(1);
	DIO_writePin(EN,LOW);
	_delay_ms(1);

	DIO_writePin(D7,READ_BIT(ins,3));
	DIO_writePin(D6,READ_BIT(ins,2));
	DIO_writePin(D5,READ_BIT(ins,1));
	DIO_writePin(D4,READ_BIT(ins,0));
	DIO_writePin(EN,HIGH);
	_delay_ms(1);
	DIO_writePin(EN,LOW);
	_delay_ms(1);
}

void LCD_voidInit(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0C);	//0x0E , 0x0F
	WriteIns(0x01); //clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

static void WriteData(u8 data)
{
	DIO_writePin(RS,HIGH);
	DIO_writePin(D7,READ_BIT(data,7));
	DIO_writePin(D6,READ_BIT(data,6));
	DIO_writePin(D5,READ_BIT(data,5));
	DIO_writePin(D4,READ_BIT(data,4));
	DIO_writePin(EN,HIGH);
	_delay_ms(1);
	DIO_writePin(EN,LOW);
	_delay_ms(1);

	DIO_writePin(D7,READ_BIT(data,3));
	DIO_writePin(D6,READ_BIT(data,2));
	DIO_writePin(D5,READ_BIT(data,1));
	DIO_writePin(D4,READ_BIT(data,0));
	DIO_writePin(EN,HIGH);
	_delay_ms(1);
	DIO_writePin(EN,LOW);
	_delay_ms(1);
}

#elif _8_BIT_
static void WriteIns(u8 ins)
{
	DIO_writePin(RS,LOW);
	DIO_writePort(LCD_PORT,ins);  //8 Bit LCD
	DIO_writePin(EN,HIGH);
	_delay_ms(1);
	DIO_writePin(EN,LOW);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x38);
	WriteIns(0x0C);	//0x0E , 0x0F
	WriteIns(0x01); //clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

static void WriteData(u8 data)
{
	DIO_writePin(RS,HIGH);
	DIO_writePort(LCD_PORT,data);  //8 Bit LCD
	DIO_writePin(EN,HIGH);
	_delay_ms(1);
	DIO_writePin(EN,LOW);
}
#endif

void LCD_voidGoTo(u8 line,u8 cell)
{
	if(line==0)
	{
		WriteIns(LINE1_START_ADD+cell);
		line_Counter=cell;
	}
	else if(line==1)
	{
		WriteIns(LINE2_START_ADD+cell);
		line_Counter=cell;
	}
	flag=line;
}

void LCD_voidWriteChar(u8 ch)
{
	/*
	if(flag==0&&line_Counter>15)
	{
	LCD_GoTo(1,0);
	line_Counter=0;
	}
	if(flag==1&&line_Counter>15)
	{
	LCD_GoTo(0,0);
	line_Counter=0;
	}*/
	WriteData(ch);
	//line_Counter++;
}

void LCD_voidWriteString(c8*str)
{
	for(u8 i=0;str[i];i++)
	{
		WriteData(str[i]);
	}
}

void LCD_voidWriteNumber(u32 num)
{
	u8 str[10],i;
	
	if(num==0)
	{
		LCD_voidWriteChar('0');
	}
	if(num<0)
	{
		LCD_voidWriteChar('-');
		num=num*(-1);
	}
	for(i=0;num>0;i++)
	{
		str[i]=num%10+'0';
		num=num/10;
	}
	i--;
	for(;i!=255;i--)
	{
		LCD_voidWriteChar(str[i]);
	}
}

void LCD_WriteBinary2(u8 num)
{
	u8 i,bit=31,flag=0;
	for(i=0;bit!=255;bit--)
	{
		if(num&(1<<(bit)))
		{
			LCD_voidWriteChar('1');
			flag=1;
			i++;
		}
		else
		{
			if(flag==1)
			{
				LCD_voidWriteChar('0');
				i++;
			}
		}
	}
}

void LCD_voidWriteBinary(u8 num)
{
	for(s8 bit=7;bit>=0;bit--)
	{
		LCD_voidWriteChar((READ_BIT(num,bit)+'0'));
	}
}


void LCD_WriteHex(u8 num)
{
	u8 HN=num>>4;
	u8 LN=num&0x0F;
	
	if(HN<10)
	LCD_voidWriteChar(HN+'0');
	else
	LCD_voidWriteChar(HN-10+'A');
	
	if(LN<10)
	LCD_voidWriteChar(LN+'0');
	else
	LCD_voidWriteChar(LN-10+'A');
}

void LCD_voidWrite4D(u16 num)
{
	LCD_voidWriteChar(((num%10000)/10000)+'0');
	LCD_voidWriteChar(((num%1000)/1000)+'0');
	LCD_voidWriteChar(((num%100)/100)+'0');
	LCD_voidWriteChar(((num%10))+'0');
}

void LCD_Clear(void)
{
	WriteIns(0x01); //clear screen
	_delay_ms(1);
}


void LCD_CustomChar(u8 address, u8*pattern)
{
	WriteIns(0x40+address*8);
	for(u8 i=0;i<8;i++)
	WriteData(pattern[i]);
	WriteIns(0x80);
}


void LCDclearGoTo(u8 line,u8 cell,u8 cellsNo)
{
	LCD_voidGoTo(line,cell);
	for(s8 i=0;i<cellsNo;i++)
	{
		LCD_voidWriteChar(' ');
	}
}


void LCDtransitionRight(u8 cells,u8 time)
{
	for(u8 i=0;i<cells;i++)
	{
		WriteIns(0x1C);
		for(u8 j=0;j<time;j++)
		{
			_delay_ms(1);
		}
	}
}

void LCDtransitionLeft(u8 cells,u8 time)
{
	for(u8 i=0;i<cells;i++)
	{
		WriteIns(0x18);
		for(u8 j=0;j<time;j++)
		{
			_delay_ms(1);
		}
	}
}

void LCD_voidIntro(c8*str1,c8*str2,c8*str3)
{
	LCD_voidGoTo(0,5);
	LCD_voidWriteString(str1);
	_delay_ms(3000);

	
	LCDclearGoTo(0,0,16);
	LCDclearGoTo(1,0,16);
	LCD_voidGoTo(0,2);
	LCD_voidWriteString(str2);
	LCD_voidGoTo(1,0);
	LCD_voidWriteString(str3);

	_delay_ms(3000);
	LCD_Clear();
}

void LCD_voidWriteStringGoTo(u8 line,u8 cell,c8*str)
{
	LCD_voidGoTo(line,cell);
	LCD_voidWriteString(str);
}

void LCD_voidMovString(u8 line,c8*str) //Not Compeleted
{
	u8 strCounter=0,time=10;
	s8 cells=15,counter=0,counterd=0;
	u8 flag=0;
	for(;str[strCounter];strCounter++);
	if(flag==0)
	{
		for(cells=15;cells>=0;cells--)
		{
			LCD_voidGoTo(line,cells);
			for(counter=0;counter<strCounter;counter++)
			{
				LCD_voidWriteChar(str[counter]);
				_delay_ms(10);
			}
			LCDclearGoTo(line,0,16);
		}
		flag=1;
		counterd=1;
		time=1;
	}
	if(flag==1)
	{
		while(counterd!=strCounter)
		{
			LCD_voidGoTo(line,cells);
			for(counter=counterd;counter<strCounter;counter++)
			{
				LCD_voidWriteChar(str[counter]);
				for(s8 i=0;i<time;i++)
				_delay_ms(1);
			}
			LCDclearGoTo(line,0,16);
			time*=2;
			counterd++;
		}
		flag=0;
	}
}

