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

ISR (__vector_11);
ISR (__vector_5);

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
	
US_Init(TIMER_0);

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

//Timer0 Overflow ISR
ISR (__vector_11){ 
	overflows_0++;
}

//Timer2 Overflow
ISR (__vector_5){ 
	overflows_2++;
}
