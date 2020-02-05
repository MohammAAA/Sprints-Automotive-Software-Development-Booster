#include "types.h"
#include "GPIO.h"
#include <util/delay.h>
#include <stdio.h>
#include "Timers.h"
#include "US.h"

volatile uint8 int_flag =0;
volatile uint16 overflows_0;
volatile uint16 overflows_2;
volatile uint8 flag = 1; //positive edge trigger indicator
volatile uint8 flag_timer = 0; // if =0 so timer 0 is used ,, if =2 then timer 2 is used
volatile uint16 Distance =0;

ISR (__vector_3);

void US_Init(uint8 Timer_Select)
{
	Timer_init (Timer_Select, OF_INT);
	GPIO_Direction(PORTA, 1, OUTPUT);
	GPIO_Direction(PORTA, 6, OUTPUT);
	SETBIT(SREG,7);  //Enable Global INT
	SETBIT(GICR,5); //External INT2 Activation // General Interrupt control register
}

void US_Start (uint8 US_Select){
	switch (US_Select){
		case US_FRONT:
		GPIO_Set_Value(PORTA,1, HIGH); // sending 10us pulse
		SETBIT(MCUCSR,6); // configuring INT2 to be +ve edge triggered
		_delay_ms(200);
		CLRBIT(PORTA,1); //GPIO_Set_Value(PORTA,1, LOW);
		while (int_flag == 0);
		break;
			
		case US_SIDE:
		GPIO_Set_Value(PORTA,6, HIGH); // sending 10us pulse
		SETBIT(MCUCSR,6); // configuring INT2 to be +ve edge triggered
		_delay_ms(200);
		CLRBIT(PORTA,6); //GPIO_Set_Value(PORTA,1, LOW);
		while (int_flag == 0);
		break;
	}
		
}

ISR (__vector_3)
{
	int_flag = 0;
	uint8 current_count;
	uint16 counts;
	switch (flag)
	{
		case POSITIVE_EDGE:
		switch (flag_timer)
		{
			case TIMER_0:
			flag = 0;
			TCNT0 = 0x00;
			Timer_Set_Prescaler(TIMER_0, PRE_1024);
			CLRBIT(MCUCSR,6);  // configuring INT2 to be -ve edge triggered
			SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
			break;

			case TIMER_2:
			flag = 0;
			TCNT2 = 0x00;
			CLRBIT(MCUCSR,6);  // configuring INT2 to be -ve edge triggered
			SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
			break;
		}
		break;

		case NEGATIVE_EDGE:
		int_flag = 1;

		switch (flag_timer)
		{
			case TIMER_0:
			Timer_Set_Prescaler(TIMER_0, PRE_0);
			current_count = (TCNT0);   //GPIO_Get_Reg(TCNT0);
			counts = current_count + (256*overflows_0);
			Distance = (34000 * PRE_1024*counts)/16000000;
			overflows_0 = 0;
			TCNT0 = 0x00;
			flag =1;
			SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
			break;

			case TIMER_2:
			current_count = (TCNT2);
			counts = current_count + (256*overflows_2);
			Distance = (34000 * PRE_256*counts)/16000000;
			overflows_2 = 0;
			TCNT2 = 0x00;
			flag =1;
			SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt

			break;
		}
		break;
}
}
