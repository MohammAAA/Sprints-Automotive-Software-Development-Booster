/*
TCNT1 is the timer immediate counter
OCR1A is the compare value
OCA1 is the automatic PWM output
Fast 10 bit PWM has top value of 1023 
compare value = Duty Cycle * 1023
*/
#include "Motor_types.h"
#include "PWM.h"
#include "MACROS.h"
#include <avr/io.h>


void PWM_Init(void)
{
	//this to select Fast PWM,10-bit mode
	SETBIT(TCCR1A,WGM10);
	SETBIT(TCCR1A,WGM11);
	SETBIT(TCCR1B,WGM12);
	
	//this to make PWM non-inverting mode
	//clear on compare - set on TOP
	CLRBIT(TCCR1A,COM1A0);
	SETBIT(TCCR1A,COM1A1);
	CLRBIT(TCCR1A,COM1B0);
	SETBIT(TCCR1A,COM1B1);
	
}

// change prescaling value of the PWM 
// input should be one of these (1,8,64,256,1024)
void Set_PWM_Prescaling_Value(uint16 Prescaler)
{
	switch (Prescaler)
	{
		case 1:
		{
			SETBIT (TCCR1B,CS10);
			CLRBIT (TCCR1B,CS11);
			CLRBIT (TCCR1B,CS12);
			break;
		}
		case 8:
		{
			CLRBIT (TCCR1B,CS10);
			SETBIT (TCCR1B,CS11);
			CLRBIT (TCCR1B,CS12);
			break;
		}
		case 64:
		{
			SETBIT (TCCR1B,CS10);
			SETBIT (TCCR1B,CS11);
			CLRBIT (TCCR1B,CS12);
			break;
		}
		case 256: 
		{
			CLRBIT (TCCR1B,CS10);
			CLRBIT (TCCR1B,CS11);
			SETBIT (TCCR1B,CS12);
			break;
		}
		case 1024:
		{
			SETBIT (TCCR1B,CS10);
			CLRBIT (TCCR1B,CS11);
			SETBIT (TCCR1B,CS12);
			break;
		}
		default:
			break;
	}
}

// change the duty cycle of the PWM and store in the OCR1A
void SetDutyCycle(uint16 Motor_n , uint16 DutyCycle_perc)
{
	uint16 comp_Val=0;
		
	if (MOTOR_1 == Motor_n)
	{
		comp_Val = ((float)DutyCycle_perc/100.0) * 1023.0;
		OCR1A = comp_Val;
	}
	if (MOTOR_2 == Motor_n)
	{
		comp_Val = ((float)DutyCycle_perc/100.0) * 1023.0;
		OCR1B = comp_Val;
	}
}