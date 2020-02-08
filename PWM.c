/*
PWM Driver:
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


/* Initialize the PWM peripheral by setting its mode of operation
** Pre-conditions: None
** Post-conditions: PWM is initialized and ready to operate
** Input arguments: None
** Return: None
*/
void PWM_Init(void)
{
	//select Fast PWM,10-bit mode
	SETBIT(TCCR1A,WGM10);
	SETBIT(TCCR1A,WGM11);
	SETBIT(TCCR1B,WGM12);
	
	//make PWM non-inverting mode, clear on compare - set on TOP
	CLRBIT(TCCR1A,COM1A0);
	SETBIT(TCCR1A,COM1A1);
	CLRBIT(TCCR1A,COM1B0);
	SETBIT(TCCR1A,COM1B1);
	
}


/* This function specifies the PWM prescaler value 
** Pre-conditions: None
** Post-conditions: PWM clock is set
** Input arguments: Prescaling value
** Return: None
*/
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


/* This function sets the duty cycle of the PWM to be used in the motors speed control 
** Pre-conditions: PWM is initialized and prescaler value is set
** Post-conditions: PWM duty cycle is modified
** Input arguments: Motor number, duty cycle percentage "ON time percentage"
** Return: None
*/
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
