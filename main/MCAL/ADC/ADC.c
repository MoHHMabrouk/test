#define F_CPU 16000000
#include <util/delay.h>
#include "stdTypes.h"
#include "memMap.h"
#include "utils.h"
#include "ADC_interface.h"
//#include "Sensors_cfg.h"

static adcBusyFlagType adcBusyFlag=PROCESSING;

void ADC_Init(voltRefType vref,prescalarType prescalar)
{
	/* vref */
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	/* prescaler */
	
	ADCSRA&=0xF8;
	prescalar&=0x07;
	ADCSRA|=prescalar;
	
	/* Enable ADC */
	SET_BIT(ADCSRA,ADEN);
}


u16 ADC_Read(channalType ch)
{

	/* set channal mux */
	
	ADMUX&=0xE0;
	ADMUX|=ch;
	
	/* start conversion */
	
	SET_BIT(ADCSRA,ADSC);
	
	/* w8 ADC finish */
	while(READ_BIT(ADCSRA,ADSC));
	/* get read */
	/* Right Adjust */

	/*adc=ADCL;
	adc|=(ADCH<<8);*/  //any number by default int
	
	/* Left Adjust */
	
	/*adc=ADCL>>6;
	adc|=ADCL<<2;*/
	
	return ADC;
}

void adcStartConversion(channalType ch)
{
	if(adcBusyFlag==READY)
	{
		/* set channal mux */
		
		ADMUX&=0xE0;
		ADMUX|=ch;
		
		/* start conversion */
		
		SET_BIT(ADCSRA,ADSC);
		adcBusyFlag=PROCESSING;
	}
}

u8 adcGetReadPeriodic(u16*pdata)
{
	if(!(READ_BIT(ADCSRA,ADSC)))
	{
		*pdata=ADC;
		adcBusyFlag=READY;
		return 1;
	}
	return 0;
}

u16 adcGetReadNoBlocking(void)
{
	return ADC;
}


u16 ADC_voltRead(channalType ch)
{
	u16 volt;
	
	u16 adc=ADC_Read(ch);

	volt=((u32)adc*VREF)/1024;
	
	return volt;
}

u16 adcInterpolation(u16 y1,u16 y2,u16 x,u16 x1,u16 x2)
{
	u16 y=((((y2-(s32)y1)*((s32)x-x1))/((s32)x2-x1))+y1);
	//u16 y=(((((y2-y1)*(u32)(x-x1))+((x2-x1)/2))/(x2-x1))+y1); // bygeb resolution a3la lec 51 min 20 check if forget
	return y;
}