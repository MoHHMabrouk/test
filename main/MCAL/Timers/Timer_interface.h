#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
#include "stdTypes.h"


/******************* TIMER0 *******************/

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PWM_PHASE_CORRECT_MODE,
	TIMER0_CTC_MODE,
	TIEMR0_FAST_PWM_MODE
}TIMER0_mode_t;

typedef enum
{
	TIMER0_preScalar_0=0,
	TIMER0_preScalar_1,
	TIMER0_preScalar_8,
	TIMER0_preScalar_64,
	TIMER0_preScalar_256,
	TIMER0_preScalar_1024,
	TIMER0_EX_CLK_FALLING_EDGE,
	TIMER0_EX_CLK_RISING_EDGE
}TIMER0_preScalar_t;

typedef enum
{
	OCR0_DISCONNECTED,
	OCR0_TOGGLE,
	OCR0_NON_INVERTING,
	OCR0_INVERTING
}TIMER0_OCR0_t;

void TIMER0_voidInit(TIMER0_mode_t mode,TIMER0_preScalar_t preScalar);

void TIMER0_voidSetTCNT0(u8 copy_u8_time);

void TIMER0_voidSetOCR0(u8 copy_u8_OCR0);

void TIMER0_voidOCR0Mode(TIMER0_OCR0_t mode);

void TIMER0_voidOVFSetCallBack(void (*copy_u8_ptr)(void));

void TIMER0_voidOVFInterruptEnable(void);

void TIMER0_voidOVFInterruptDisable(void);

void TIMER0_voidOCR0InterruptEnable(void);

void TIMER0_voidOCR0InterruptDisable(void);


/******************* TIMER1 *******************/


typedef enum{
	TIMER1_STOP=0,
	TIMER1_preScaler_1,
	TIMER1_preScaler_8,
	TIMER1_preScaler_64,
	TIMER1_preScaler_256,
	TIMER1_preScaler_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}TIMER1_preScaler_t;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}TIMER1_mode_t;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_mode_t;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_mode_t;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;




void TIMER1_voidInputCaptureEdge(ICU_Edge_type edge);
void TIMER1_voidInit(TIMER1_mode_t mode,TIMER1_preScaler_t scaler);
void TIMER1_voidOCRA1Mode(OC1A_mode_t OC1A_mode);
void TIMER1_voidOCRB1Mode(OC1B_mode_t OC1B_mode);


void TIMER1_ICU_voidInterruptEnable(void);
void TIMER1_ICU_voidInterruptDisable(void);

void TIMER1_OVF_voidInterruptEnable(void);
void TIMER1_OVF_voidInterruptDisable(void);

void TIMER1_OCA_voidInterruptEnable(void);
void TIMER1_OCA_voidInterruptDisable(void);

void TIMER1_OCB_voidInterruptEnable(void);
void TIMER1_OCB_voidInterruptDisable(void);

void TIMER1_OVF_voidSetCallBack(void(*LocalFptr)(void));
void TIMER1_OCA_voidSetCallBack(void(*LocalFptr)(void));
void TIMER1_OCB_voidSetCallBack(void(*LocalFptr)(void));
void TIMER1_ICU_voidSetCallBack(void(*LocalFptr)(void));


#endif /* TIMER_INTERFACE_H_ */