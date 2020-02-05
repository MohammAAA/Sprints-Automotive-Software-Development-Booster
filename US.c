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
volatile uint16 temp = 0;
volatile uint16 bta3 = 0;

ISR (__vector_3);

void US_Init(uint8 Timer_Select)
{
	Timer_init (Timer_Select, OF_INT);
	//Timer_Set_Prescaler(TIMER_0, PRE_1024);
	GPIO_Direction(PORTA, 1, OUTPUT);
	SETBIT(SREG,7);  //Enable Global INT
	SETBIT(GICR,5); //External INT2 Activation // General Interrupt control register
	//printf("US_Init Success");
}

void US_Start (void){

	GPIO_Set_Value(PORTA,1, HIGH); // sending 10us pulse
	//SETBIT(MCUCR,0);  // configuring INT0 to be +ve edge triggered
	//SETBIT(MCUCR,1);
	SETBIT(MCUCSR,6); // configuring INT2 to be +ve edge triggered
	//SETBIT(GIFR,5); //General Interrupt flag register, flag to check that indicates interrupt occurance
	_delay_ms(200);
	CLRBIT(PORTA,1); //GPIO_Set_Value(PORTA,1, LOW);
	while (int_flag == 0);
	// 3'alaaat while ((GIFR >> INTF2) == 0);
//	printf("US_Start Success");
//DDRA = 0xFF;
//PORTA=0xFF;

}

//uint16 US_Get_Distance (void){
//uint16 temp; //= Distance;
//$$ temp = Distance;
//$$ bta3 = Distance;


//PORTB = PORTB | 0b10000000;
//$$ while (temp == bta3){
//$$	bta3 = Distance;
//$$ }
//	printf("US_Get_Distance Success");
//PORTB = PORTB | 0b01000000;
//return Distance;


// msh 3ayzo ybd2 3'er lamma el interrupt bta3 el -ve edge yeegy (y3ny el +ve y7sl wb3den el -ve y7sl)

// msh h return 3'er lamma el distance tt'3ayr

//}



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
					overflows_2 = 0;
					TCNT2 = 0x00;
					flag =1;
					SETBIT(GIFR,5); //INTF2 is set to be able to get a new interrrupt

				break;
			}

		break;

	}
}
