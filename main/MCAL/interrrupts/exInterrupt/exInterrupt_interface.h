#ifndef EXINTERRUPT_INTERFACE_H_
#define EXINTERRUPT_INTERFACE_H_

typedef enum
{
	EX_INT0,
	EX_INT1,
	EX_INT2
}exInterruptSource_t;

typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}triggerEdge_t;

void exInterrupt_voidEnable(exInterruptSource_t interrupt);
void exInterrupt_voidDisable(exInterruptSource_t interrupt);
void exInterrupt_voidTriggerEdge(exInterruptSource_t interrupt,triggerEdge_t triggerEdge);
void exInterrupt_voidSetCallBack(exInterruptSource_t interrupt,void (*localPtr)(void));

#endif /* EXINTERRUPT_INTERFACE_H_ */