#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
#include "stdTypes.h"
#define VREF 5000UL

typedef enum
{
	VREF_AREF,
	VREF_AVCC,
	VREF_256V
}voltRefType;

typedef enum
{
	ADC_SCALAR_2=1,
	ADC_SCALAR_4,
	ADC_SCALAR_8,
	ADC_SCALAR_16,
	ADC_SCALAR_32,
	ADC_SCALAR_64,
	ADC_SCALAR_128
}prescalarType;

typedef enum
{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}channalType;

typedef enum
{
	READY,
	PROCESSING
}adcBusyFlagType;


void ADC_Init(voltRefType vref,prescalarType prescalar);
u16 ADC_Read(channalType ch);

/* return mv */
u16 ADC_voltRead(channalType ch);
u16 adcGetReadNoBlocking(void);
void adcStartConversion(channalType ch);



#endif /* ADC_INTERFACE_H_ */