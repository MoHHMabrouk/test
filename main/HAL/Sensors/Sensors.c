#include "Sensors_interface.h"
#include "stdTypes.h"

void LM35_voidInit(voltRefType VREF_SELECT,prescalarType SCALAR)
{
	ADC_Init(VREF_SELECT,SCALAR);
}

void LDR_voidInit(voltRefType VREF_SELECT,prescalarType SCALAR)
{
	ADC_Init(VREF_SELECT,SCALAR);
}

u16 LM35_u16GetRead(channalType ch)
{
	u16 adc=ADC_Read(ch);
	u16 temp=(adc*(u32)VREF)/1024;
	return temp;
}

u16 LDR_u16GetRead(channalType ch)
{
	u16 adc=ADC_Read(ch);
	return adc;
}