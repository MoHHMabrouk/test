#define F_CPU 16000000

#include <util/delay.h>

#include "SSD_interface.h"
#include "DIO_interface.h"
#include "SSD_cfg.h"

void SSD_displayDigit(SSDType ssd,u8 num)
{
	switch(ssd)
	{
		case SSD1:
		DIO_writePin(SSD1_COM,LOW);
		DIO_writePin(SSD2_COM,HIGH);
		DIO_writePin(SSD3_COM,HIGH);
		DIO_writePin(SSD4_COM,HIGH);
		break;

		case SSD2:
		DIO_writePin(SSD1_COM,HIGH);
		DIO_writePin(SSD2_COM,LOW);
		DIO_writePin(SSD3_COM,HIGH);
		DIO_writePin(SSD4_COM,HIGH);
		break;
		
		case SSD3:
		DIO_writePin(SSD1_COM,HIGH);
		DIO_writePin(SSD2_COM,HIGH);
		DIO_writePin(SSD3_COM,LOW);
		DIO_writePin(SSD4_COM,HIGH);
		break;
		
		case SSD4:
		DIO_writePin(SSD1_COM,HIGH);
		DIO_writePin(SSD2_COM,HIGH);
		DIO_writePin(SSD3_COM,HIGH);
		DIO_writePin(SSD4_COM,LOW);
		break;
	}
	
	DIO_writePin(SSD_DECODER_PIN01,(num>>0)&1);
	DIO_writePin(SSD_DECODER_PIN02,(num>>1)&1);
	DIO_writePin(SSD_DECODER_PIN03,(num>>2)&1);
	DIO_writePin(SSD_DECODER_PIN04,(num>>3)&1);
}

void SSD_displayNumber(u16 num)
{
	unsigned char digitsArr[4];
	for(int i=0;i<4;i++)
	{
		digitsArr[i]=num%10;
		num/=10;
	}
	for(u8 counter=0;counter<SSD_DELAY;counter++)
	{
		for(SSDType SSDnum=SSD1;SSDnum<=SSD4;SSDnum++)
		{
			SSD_displayDigit(SSDnum,digitsArr[SSDnum]);
			_delay_ms(1);
		}
	}

}