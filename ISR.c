#include "MACROS.h"
#include "types.h"
#include "ISR.h"
#include "GPIO.h"
#include "US.h"


volatile uint16 overflows_0;
volatile uint16 overflows_2;

ISR (__vector_5);
ISR (__vector_11);


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
