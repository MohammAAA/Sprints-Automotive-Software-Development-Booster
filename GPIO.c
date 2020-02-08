#include "GPIO.h"

/* This function specifies the direction of a specific pin in a specific port
** Pre-conditions: None
** Post-conditions: Pin direction is specified and updated
** Input arguments: Port number, number of bit to be directed, direction whether INPUT or OUTPUT
** Return: void
*/
void GPIO_Direction(uint8 PORTx, uint8 nbit, uint8 Direction )
{
	if(PORT__A==PORTx)

	  {
    	  if (Direction==OUTPUT)
	        {
		       SETBIT(DDRA,nbit);
	        }

	else if (Direction==INPUT)
	        {
		       CLRBIT(DDRA, nbit);
	        }
	 }

	 if(PORT__B==PORTx)

	 {
		 if (Direction==OUTPUT)
		 {
			 SETBIT(DDRB,nbit);
		 }

		 else if (Direction==INPUT)
		 {
			 CLRBIT(DDRB, nbit);
		 }
	 }

	 if(PORT__C==PORTx)

	 {
		 if (Direction==OUTPUT)
		 {
			 SETBIT(DDRC,nbit);
		 }

		 else if (Direction==INPUT)
		 {
			 CLRBIT(DDRC, nbit);
		 }
	 }

	 if(PORT__D==PORTx)

	 {
		 if (Direction==OUTPUT)
		 {
			 SETBIT(DDRD,nbit);
		 }

		 else if (Direction==INPUT)
		 {
			 CLRBIT(DDRD, nbit);
		 }
	 }
}




/* This function sets the value of the specific pin whether it's HIGH or LOW
** Pre-conditions: Pin is set as OUTPUT
** Post-conditions: Pin value is specified and updated
** Input arguments: Port number, number of bit to be updated, update value whether HIGH or LOW
** Return: void
*/
extern void GPIO_Set_Value(uint8 Port ,uint8 Copy_u8PinNum, uint8 Copy_u8PinValue)
{
	switch (Port)
	{
		case PORT__A:
		if (Copy_u8PinValue==1)
			SETBIT(PORTA,Copy_u8PinNum);
		else
			CLRBIT(PORTA,Copy_u8PinNum);
		break;

		case PORT__B:
		if (Copy_u8PinValue==1)
			SETBIT(PORTB,Copy_u8PinNum);
		else
			CLRBIT(PORTB,Copy_u8PinNum);
		break;

		case PORT__C:
		if (Copy_u8PinValue==1)
			SETBIT(PORTC,Copy_u8PinNum);
		else
			CLRBIT(PORTC,Copy_u8PinNum);
		break;

		case PORT__D:
		if (Copy_u8PinValue==1)
			SETBIT(PORTD,Copy_u8PinNum);
		else
			CLRBIT(PORTD,Copy_u8PinNum);
		break;
	}
}


/* This function reads the value of the specific pin whether it's HIGH or LOW
** Pre-conditions: Pin is set as OUTPUT
** Post-conditions: None
** Input arguments: Port number, number of pin to be read
** Return: Explicit return of the value of the pin to be read
*/
uint8 GPIO_Read(uint8 Port, uint8 PinNum) {
return GET_BIT(Port, PinNum);
}


/* This function the global interrupt enable pin which is in SREG register
** Pre-conditions: None
** Post-conditions: Global interrupt is enabled so that all interrupts can be operated
** Input arguments: None
** Return: None
*/
void Enable_INT(void)
{
	SETBIT(SREG, 7); //enable global interrupt
}

/* This function reads the value of the whole port whether it's HIGH or LOW
** Pre-conditions: Port is set as OUTPUT
** Post-conditions: Port value is read
** Input arguments: Port number
** Return: Explicit return the port value
*/
uint8 GPIO_Get_Reg (uint8 Port) {
	return (Port & 0xFF);
}
