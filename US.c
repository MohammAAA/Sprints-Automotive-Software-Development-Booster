
/* Ultrasonic sensor driver*/

#define F_CPU 16000000
#include "types.h"
#include "GPIO.h"
#include <util/delay.h>
#include "Timers.h"
#include "US.h"

volatile uint8 US_Number =0;
volatile uint8 int_flag =0;
volatile uint8 positive_edge_flag = 1; //positive edge trigger indicator
volatile uint8 flag_timer = 0; // if =0 so timer 0 is used ,, if =2 then timer 2 is used
volatile uint16 overflows_0;
volatile uint16 overflows_2;
volatile uint16 Distance_Front =0;
volatile uint16 Distance_Side =0;


ISR (__vector_3);


/* Initialize the ultrasonic sensor 
** Pre-conditions: None
** Post-conditions: ultrasonic is initialized
** Input arguments: specification of the timer which will operate with the US
** Return: None
*/
void US_Init(uint8 Timer_Select)
{
	Timer_init (Timer_Select, OF_INT);
	GPIO_Direction(PORTA, 1, OUTPUT);
	GPIO_Direction(PORTA, 6, OUTPUT);
	Enable_INT(); //Enable Global INT
	SETBIT(GICR,5); //External INT2 Activation // General Interrupt control register
}



/* Start operating the ultrasonic sensor 
** Pre-conditions: Ultrasonic is initialized
** Post-conditions: ultrasonic is started and the distance value is updated with a new one
** Input arguments: selection of the ultrasonic sensor
** Return: None
*/
void US_Start (uint8 US_Select){
	if (US_Select == US_FRONT){
		US_Number = US_FRONT;
				SETBIT (PORTA, 1); // start sending 10us pulse for the US_FRONT
				CLRBIT (PORTA, 6); //make sure the US_SIDE is off
				SETBIT(MCUCSR,6); // configuring INT2 to be +ve edge triggered
				_delay_ms(20);
				CLRBIT (PORTA, 1); //GPIO_Set_Value(PORTA,1, LOW); //ending pulse
				while (int_flag == 0); //function is only terminated in case of the Distance variable is updated
	}
	else if (US_Select == US_SIDE){
		US_Number = US_FRONT;
				GPIO_Set_Value(PORTA,6, HIGH); // start sending 10us pulse for the US_SIDE
				CLRBIT (PORTA, 6); //make sure the US_FRONT is off
				SETBIT(MCUCSR,6); // configuring INT2 to be +ve edge triggered
				_delay_ms(20);
				GPIO_Set_Value(PORTA,6, LOW); //ending pulse
				while (int_flag == 0);
	}
}




/* external interrupt service routine
** Pre-conditions: the external interrupt pin senses a +ve edge or -ve edge echo signal
** Post-conditions: timer reset & distance value is updated
** Input arguments: None
** Return: None
*/
ISR (__vector_3)
{
int_flag = 0;
uint8 current_count;
uint16 counts;
switch (positive_edge_flag)
	{
		case POSITIVE_EDGE:

				switch (flag_timer)
				{
					case TIMER_0:
						positive_edge_flag = 0;
						TCNT0 = 0x00;
						Timer_Set_Prescaler(TIMER_0, PRE_1024);
						CLRBIT(MCUCSR,6);  // configuring INT2 to be -ve edge triggered
						SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
					break;

					case TIMER_2:
						positive_edge_flag = 0;
						TCNT2 = 0x00;
						Timer_Set_Prescaler(TIMER_2, PRE_1024);
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
					if (US_Number == US_FRONT){
						Distance_Front = (34300 * PRE_1024*counts)/32000000;
					}
					else if (US_Number == US_SIDE){
						Distance_Side = (34300 * PRE_1024*counts)/32000000;
					}
					overflows_0 = 0;
					TCNT0 = 0x00;
					positive_edge_flag =1;
					SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
				break;

				case TIMER_2:
					Timer_Set_Prescaler(TIMER_2, PRE_0);
					current_count = (TCNT2);
					counts = current_count + (256*overflows_2);
					if (US_Number == US_FRONT){
						Distance_Front = (34300 * PRE_1024*counts)/32000000;
					}
					else if (US_Number == US_SIDE){
						Distance_Side = (34300 * PRE_1024*counts)/32000000;
					}
					overflows_2 = 0;
					TCNT2 = 0x00;
					positive_edge_flag =1;
					SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt
				break;
			}

		break;
	}
}
