
/* Timers 0 & 2 Driver 
** TCCRx: Configuration registers
** TIMSK: mask register for interrupts
*/

#include "Timers.h"

extern uint8 flag_timer ;


/* This function specifies the Timerx prescaler 
** Pre-conditions: Timerx is initialized
** Post-conditions: Timerx prescaler is set
** Input arguments: Timer number, prescaling value
** Return: None
*/
void Timer_Set_Prescaler(uint8 Timer_Select, uint16 Timer_Prescaler)
{
	switch (Timer_Select)
	{
		case 0:	 // Timer 0 is selected

		switch (Timer_Prescaler)
		{
			case PRE_0:
			TCCR0 = TCCR0 & 0b11111000;
			break;

			case PRE_1:
			TCCR0 = TCCR0 | 0b00000001;
			break;

			case PRE_8:
			TCCR0 = TCCR0 | 0b00000010;
			break;

			case PRE_64:
			TCCR0 = TCCR0 | 0b00000011;
			break;

			case PRE_256:
			TCCR0 = TCCR0 | 0b00000100;
			break;

			case PRE_1024:
			TCCR0 = TCCR0 | 0b00000101;
			break;

		}
		break; // break of case 1



		case 2:	// Timer 2 is selected
		switch (Timer_Prescaler)
		{
			case PRE_1:
			TCCR2 = TCCR2 | 0b00000001;
			break;

			case PRE_8:
			TCCR2 = TCCR2 | 0b00000010;
			break;

			case PRE_32:
			TCCR2 = TCCR2 | 0b00000011;
			break;

			case PRE_64:
			TCCR2 = TCCR2 | 0b00000100;
			break;

			case PRE_128:
			TCCR2 = TCCR2 | 0b00000101;
			break;

			case PRE_256:
			TCCR2 = TCCR2 | 0b00000110;
			break;

			case PRE_1024:
			TCCR2 = TCCR2 | 0b00000111;
			break;
		}
		break;  // break of case 2

	}
}


/* This function initializes the timer 
** Pre-conditions: None
** Post-conditions: Timer is initialzed and ready to operate
** Input arguments: Timer number, state whether overflow, compare match or no interrupt
** Return: None
*/
void Timer_init (uint8 Timer_Select, uint8 Interrupt_Activation)
{
	switch (Timer_Select)
		{
			case TIMER_0:
			flag_timer = 0;
			TCCR0 = TCCR0 & 0b00000000;
			switch (Interrupt_Activation)
			{
				case NO_INT:
				TIMSK = TIMSK & 0b11111100;
				break;

				case CM_INT:
				Enable_INT();
				TIMSK = TIMSK | 0b00000010;
				break;

				case OF_INT:
				Enable_INT();
				TIMSK = TIMSK | 0b00000001;
				break;
			}
			break;




			case TIMER_2:
			flag_timer = 2;
			TCCR2 = TCCR2 & 0b00000000;
			switch (Interrupt_Activation)
				{
					case NO_INT:
					TIMSK = TIMSK & 0b00111111;
					break;

					case CM_INT:
					Enable_INT();
					TIMSK = TIMSK | 0b10000000;
					break;

					case OF_INT:
					Enable_INT();
					TIMSK = TIMSK | 0b01000000;
					break;
				}
		}



}



int Timer_read_flags (uint8 Timer_Select, uint8 Flag_ToCheck)
{

	switch (Timer_Select) {
		case TIMER_0:
		switch (Flag_ToCheck){
			case OVERFLOW_FLAG:
			return (GPIO_Read(TIFR, 0));

			case COMPARE_FLAG:
			return (GPIO_Read(TIFR, 1));

		}
		break;
		case TIMER_2:
		switch (Flag_ToCheck){
			case OVERFLOW_FLAG:
			return (GPIO_Read(TIFR, 6));

			case COMPARE_FLAG:
			return (GPIO_Read(TIFR, 7));

		}
		break;

	}

}





//******************************************************* ISRs *********************************************
