#include "GPIO.h"

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



//--------------------------------------------------------------------------------------------------
extern void GPIO_Set_Value(uint8 Port ,uint8 Copy_u8PinNum, uint8 Copy_u8PinValue)
{
	/*
	*in this function we are going to take 2 passing parameters
	*the 1st one is the number of the PIN
	*the 2nd one is the value that needed to be assigned to the pre-specified PIN
	*	its return type is void that means it has no return value
	*/
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


//added
uint8 GPIO_Read(uint8 Port, uint8 PinNum) {
return GET_BIT(Port, PinNum);
}



// added

void Enable_INT(void)
{
	SETBIT(SREG, 7); //enable global interrupt
}

uint8 GPIO_Get_Reg (uint8 Port) {
	return (Port & 0xFF);
}
