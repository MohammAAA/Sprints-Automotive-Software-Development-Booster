#include "Motor.h"
#include "GPIO.h"
#include <util/delay.h>
#include "MACROS.h"
#include "types.h"
#include "Timers.h"
#include "Motor_types.h"
#include "US.h"
//#include "Phase2_app.h"
//#include "PWM.h"


extern volatile uint16 Distance ;
extern volatile uint16 overflows_0;
extern volatile uint16 overflows_2;
//#define F_CPU 16000000

ISR (__vector_11);
ISR (__vector_5);

//int main(void)
//{
	//Motor_Init();

	//PWM_Init();
	//Set_PWM_Prescaling_Value(1);

	//setting motor direction forward
	//Motor_State(MOTOR_1,FORWARD);
	//Motor_State(MOTOR_2,FORWARD);

	/*while(1)
	{
		//Schedules the two main function calls with each timer interrupt flag (overflows_2)
		void Start_Scheduler ()
		{
				if ((overflows_2) && (Speed_Perc) && (Ob_Removed == 0))
				{
					Check_Distance_Change();
				}

				if ((overflows_2) && ((US_Reading >= 190) && (US_Reading <=210)) && (Speed_Perc))
				{
					Get_New_Phase_Info();
					Ob_Removed = 0;
				}

		}

		//Change motor speed according to each phase using Speed_Flag
		Motor_Speed_Control(MOTOR_1,Speed_Flag);
		Motor_Speed_Control(MOTOR_2,Speed_Flag);
	}
}
*/



int main (void)
{

// phase 1 //

//	Motor_Init();

	//Motor_State(MOTOR_1,FORWARD);
	/*Motor_Speed_Control(MOTOR_1,MAX_SPEED);

	Motor_State(MOTOR_2,FORWARD);
	Motor_Speed_Control(MOTOR_2,MAX_SPEED);*/


// phase 2 //

//*************************************************UltraSonic Sensor*******************************************************

SETBIT(PORTB,2);
_delay_us(10);
CLRBIT(PORTB,2);

DDRB=0b11111011;
PORTB = 0x00;
//PORTB = 0b11111011;
//_delay_ms(1000);

US_Init(TIMER_0);
//Timer_Set_Prescaler(TIMER_0, PRE_256);

while(1)
{
	US_Start();



	if (Distance < 20)
	{PORTB = 0b10001000;
		//_delay_ms(2000);
	}
	else
	{PORTB = 0b01000000;
	}
}



return 0;
}



/*ISR(__vector_3)
{

}*/

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
