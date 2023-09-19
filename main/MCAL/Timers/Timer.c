#include "Timer_interface.h"
#include "stdTypes.h"
#include "memMap.h"
#include "utils.h"

static void (*TIMER0_static_void_OVF_PTR) (void)=NULL_PTR;
static void (*TIMER0_static_void_OCR0_PTR) (void)=NULL_PTR;

static void (*Timer1_OVF_Fptr) (void)=NULL_PTR;
static void (*Timer1_OCA_Fptr) (void)=NULL_PTR;
static void (*Timer1_OCB_Fptr) (void)=NULL_PTR;
static void (*Timer1_ICU_Fptr) (void)=NULL_PTR;

/******************* TIMER0 *******************/

void TIMER0_voidInit(TIMER0_mode_t mode,TIMER0_preScalar_t preScalar)
{
	switch(mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		
		case TIMER0_PWM_PHASE_CORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		
		case TIEMR0_FAST_PWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	TCCR0&=0xF8;
	TCCR0|=preScalar;
}


void TIMER0_voidSetTCNT0(u8 copy_u8_time)
{
	TCNT0=copy_u8_time;
}

void TIMER0_voidSetOCR0(u8 copy_u8_OCR0)
{
	OCR0=copy_u8_OCR0;
}

void TIMER0_voidOCR0Mode(TIMER0_OCR0_t mode)
{
	switch(mode)
	{
		case OCR0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		
		case OCR0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		
		case OCR0_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		
		case OCR0_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}

void TIMER0_voidOVFSetCallBack(void (*copy_u8_ptr)(void))
{
	TIMER0_static_void_OVF_PTR=copy_u8_ptr;
}

void TIMER0_voidOCR0SetCallBack(void (*copy_u8_ptr)(void))
{
	TIMER0_static_void_OCR0_PTR=copy_u8_ptr;
}


void TIMER0_voidOVFInterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_voidOVFInterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_voidOCR0InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}

void TIMER0_voidOCR0InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}

ISR(TIMER0_OVF_vect)
{
	if(TIMER0_static_void_OVF_PTR!=NULL_PTR)
	{
		TIMER0_static_void_OVF_PTR();
	}
}

ISR(TIMER0_OC_vect)
{
	if(TIMER0_static_void_OCR0_PTR!=NULL_PTR)
	{
		TIMER0_static_void_OCR0_PTR();
	}
}

/******************* TIMER1 *******************/

void TIMER1_voidInit(TIMER1_mode_t mode,TIMER1_preScaler_t scaler)
{
	switch(mode)
	{
		case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}

	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}
void TIMER1_voidOCRA1Mode(OC1A_mode_t OC1A_mode)
{
	switch (OC1A_mode)
	{
		case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		
		case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
void TIMER1_voidOCRB1Mode(OC1B_mode_t OC1B_mode)
{
	switch(OC1B_mode)
	{
		case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		
		case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		
		case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
void TIMER1_voidInputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	SET_BIT(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	CLR_BIT(TCCR1B,ICES1);
}


/****************************Timer 1 Interrupt functions**************************************/

void TIMER1_ICU_voidInterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void TIMER1_ICU_voidInterruptDisable(void)
{
	CLR_BIT(TIMSK,TICIE1);
}
void TIMER1_OVF_voidInterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void TIMER1_OVF_voidInterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE1);
}
void TIMER1_OCA_voidInterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void TIMER1_OCA_voidInterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}
void TIMER1_OCB_voidInterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void TIMER1_OCB_voidInterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void TIMER1_OVF_voidSetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void TIMER1_OCA_voidSetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void TIMER1_OCB_voidSetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void TIMER1_ICU_voidSetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULL_PTR)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_Fptr!=NULL_PTR)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_Fptr!=NULL_PTR)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_Fptr!=NULL_PTR)
	{
		Timer1_ICU_Fptr();
	}
}

