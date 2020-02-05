#include "MACROS.h"
#include "types.h"
#include "ISR.h"
#include "GPIO.h"
#include "US.h"


volatile uint16 overflows_0 =0;
volatile uint16 overflows_2 =0;

// ISR (TIMER2_OVF_vect)
// {
// 			DDRB |= (3<<6);
// 			PORTB |= (3<<6);
// 	//Timer0 Overflow
// 	overflows_0 = overflows_0 + 1;
// }
// 
// ISR (TIMER0_OVF_vect)
// {
// 	//Timer2 Overflow
// 	overflows_2 = overflows_2 + 1;
// }

// ISR (INT2_vect)
// {
// 	uint16 Clock_Counts;
// 	float Pulses_Time;
// 	
// 	switch (US_Status_Flag)
// 	{
// 		case 1:
// 			switch (Timer_No)
// 			{
// 				case 0:
// 					TCNT0 = 0x00;
// 					overflows_0 = 0;
// 					CLRBIT(MCUCSR,6);  // configuring interrupt on PB2 to be -ve edge triggered
// 					US_Status_Flag = 0;
// 				break;
// 			
// 				case 2:
// 					TCNT2 = 0x00;
// 					overflows_2 = 0;
// 					CLRBIT(MCUCSR,6);  // configuring interrupt on PB2 to be -ve edge triggered
// 					US_Status_Flag = 0;
// 				break;
// 			}
// 		
// 		case 0:
// 			switch (Timer_No)
// 			{
// 				case 0:
// 					Clock_Counts = TCNT0 + (256 * overflows_0);
// 					Pulses_Time = (float)PRE_1024*(float)Clock_Counts/16000000.0;
// 					Distance = (uint16)(34300.0 * Pulses_Time);
// 					TCNT0 = 0x00;
// 					overflows_0 = 0;
// 					US_Status_Flag = 1;
// 					US_Finish_Flag = 1;
// 					//SETBIT(GIFR,5); //clear flag after interrupt occurance
// 				break;
// 			
// 				case 2:
// 					Clock_Counts = TCNT2 + (256 * overflows_2);
// 					Pulses_Time = (float)PRE_1024*(float)Clock_Counts/16000000.0;
// 					Distance = (uint16)(34300.0 * Pulses_Time);
// 					TCNT2 = 0x00;
// 					overflows_2 = 0;
// 					US_Status_Flag = 1;
// 					US_Finish_Flag = 1;
// 					//SETBIT(GIFR,5); //clear flag after interrupt occurance
// 				break;
// 			}			
// 	}
// }

ISR (__vector_11){ //Timer0 Overflow
	overflows_0++;
	//TCNT0 = 0x00;
	//PORTB = ~PORTB;
	//_delay_ms(500);

}

ISR (__vector_5){ //Timer2 Overflow
	overflows_2++;
	//TCNT2 = 0x00;
}
ISR (__vector_3)
{
//printf("I am in ISR");
int_flag = 0;
uint8 current_count;
uint16 counts;
switch (flag)
	{
		case POSITIVE_EDGE:

				switch (flag_timer)
				{
					case TIMER_0:
						//PORTB = 0b11010000;
						//_delay_ms(1000);
						//PORTB = 0x00;
						flag = 0;
						TCNT0 = 0x00;
						Timer_Set_Prescaler(TIMER_0, PRE_1024);
						/*if (TCNT0==0)
							{PORTB = PORTB | 0b11110000;
							_delay_ms(500);}
						*/
						//Timer_Set_Prescaler(TIMER_0, PRE_256);


						CLRBIT(MCUCSR,6);  // configuring INT2 to be -ve edge triggered
						SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
						//printf("Timer 0 ISR +ve edge");
						//PORTB = PORTB | 0b00100000;
						//PORTB = 0;
						//_delay_ms(500);
						//PORTB = 0xFF;
					break;

					case TIMER_2:
						flag = 0;
						TCNT2 = 0x00;
						//Timer_Set_Prescaler(TIMER_2, PRE_256);

						CLRBIT(MCUCSR,6);  // configuring INT2 to be -ve edge triggered
						SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
					break;

					/*PORTB = PORTB | 0b01110000;
					_delay_ms(2000);*/
				}
		break;

		case NEGATIVE_EDGE:
			//&& PORTB = PORTB | 0b10110000;
			int_flag = 1;

			switch (flag_timer)
			{
				case TIMER_0:
					Timer_Set_Prescaler(TIMER_0, PRE_0);
					//PORTB = PORTB | 0b11110000;
					//&& _delay_ms(10000);
					//&& PORTB = 0;
					current_count = (TCNT0);   //GPIO_Get_Reg(TCNT0);
					counts = current_count + (256*overflows_0);
					Distance = (34000 * PRE_1024*counts)/16000000;
					Distance = Distance/2;
					overflows_0 = 0;
					TCNT0 = 0x00;
					flag =1;
					SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
					//printf("Timer 0 ISR -ve edge");
					//PORTB = PORTB | 0b00000000;
					//&& _delay_ms(50000);

			//&& PORTB = PORTB | 0b11110000;
			//&& _delay_ms(1000);

				break;

				case TIMER_2:
					current_count = (TCNT2);
					counts = current_count + (256*overflows_2);
					Distance = (34000 * PRE_256*counts)/16000000;
					Distance = Distance/2;
					overflows_2 = 0;
					TCNT2 = 0x00;
					flag =1;
					SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt

				break;
			}

		break;

	}
}
