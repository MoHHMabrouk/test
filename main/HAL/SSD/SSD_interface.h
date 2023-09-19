#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_
#include "stdTypes.h"

typedef enum
{
	SSD1=0,
	SSD2,
	SSD3,
	SSD4
}SSDType;

void SSD_init(void);

void SSD_displayNumber(u16 num);

void SSD_displayDigit(SSDType ssd,u8 num);

#endif /* SSD_INTERFACE_H_ */