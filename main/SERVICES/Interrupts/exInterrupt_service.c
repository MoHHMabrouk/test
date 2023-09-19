#include "exInterrupt_interface.h"
#include "exInterrupt_service_private.h"
#include "Timer_interface.h"
#include "memMap.h"
static volatile u16 flag,t1,t2,t3,ton,toff,c=0;
void PWM_exInterruptInit(void)
{
	exInterrupt_voidSetCallBack(EX_INT0,PWM);
	exInterrupt_voidTriggerEdge(EX_INT0,RISING_EDGE);
	exInterrupt_voidEnable(EX_INT0);
	TIMER1_voidInit(TIMER1_NORMAL_MODE,TIMER1_preScaler_64);
	TIMER1_OVF_voidSetCallBack(counter);
	TIMER1_OVF_voidInterruptEnable();
}

static void counter(void)
{
	c++;
}

static void PWM(void)
{
	if(flag==0)
	{
		//TCNT1=0;
		t1=TCNT1;
		c=0;
		flag=1;
		exInterrupt_voidTriggerEdge(EX_INT0,FALLING_EDGE);
	}
	else if(flag==1)
	{
		t2=TCNT1;
		flag=2;
		ton=((t2-t1+(c*MAX_U16))*4);
		c=0;
		exInterrupt_voidTriggerEdge(EX_INT0,RISING_EDGE);
	}
	else if(flag==2)
	{
		t3=TCNT1;
		toff=((t3-t2+(c*MAX_U16))*4);
		//t1=t3;
		c=0;
		//exInterrupt_voidTriggerEdge(EX_INT0,FALLING_EDGE);
		flag=3;
	}
}

void PWM_exInterrupt(u16 *pDuty,u32 *pFreq)
{
	if(flag==3)
	{
		*pDuty=(((u32)ton*100)/(ton+toff));
		*pFreq=((u32)1000000/(ton+toff));
		flag=0;
	}
}