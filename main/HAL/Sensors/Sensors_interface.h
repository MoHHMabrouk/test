#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_
#include "ADC_interface.h"
#include "stdTypes.h"

void LM35_voidInit(voltRefType VREF_SELECT,prescalarType SCALAR);

u16 LM35_u16GetRead(channalType ch);

void LDR_voidInit(voltRefType VREF_SELECT,prescalarType SCALAR);

u16 LDR_u16GetRead(channalType ch);

#endif /* SENSORS_INTERFACE_H_ */