//#define F_CPU 16000000
#include "Motor.h"
#include "GPIO.h"
#include <util/delay.h>
#include "MACROS.h"
#include "types.h"
#include "Timers.h"
#include "Motor_types.h"
#include "US.h"
#include "Phase2_app.h"
#include "PWM.h"


extern volatile uint16 Distance_Front;
extern volatile uint16 Distance_Side;
extern volatile uint16 overflows_0;
extern volatile uint16 overflows_2;


ISR (__vector_11);
ISR (__vector_5);

int main(void)
{
	US_Init(TIMER_0);
	Motor_Init();
	PWM_Init();
	Set_PWM_Prescaling_Value(1024)
		
while(1)
{
	
	US_Start(US_FRONT);
    	if (Distance_Front>FRONT_LIMIT){
	// MOTOR should be moving forward
	// OPERATE MOTOR
	Motor_State (Motor_1, FORWARD);
	Motor_State (Motor_2, FORWARD);
	Motor_Speed_Control(MOTOR_1, 30);
	Motor_Speed_Control(MOTOR_2, 30);
		break;
	}
	
	
	// The code will not pass US_Start unless it gets a value for distance, due to the while loop in US_Start function which checks the flag
	// int_flag which is only changed from 1 to 0 in the negative edge cycle of the Interrupt
	
	else if (Distance_Front<FRONT_LIMIT)
	{
		US_Start(US_SIDE);
		Motor_State (Motor_1, STOP);
		Motor_State (Motor_2, STOP);
	}
	// ROTATE LEFT
	if (Distance_Side>SIDE_MAX && Distance_Front<FRONT_LIMIT)
	{
		US_Start(US_FRONT);
		// MOTOR ROTATES TO THE LEFT
		Motor_Turn_Left();		
	}
	
	if(Distance_Front<FRONT_LIMIT && Distance_Side<SIDE_LIMIT)
	{
		US_Start(US_FRONT);
		//MOTOR ROTATES TO THE RIGHT	.
		Motor_Turn_Right();
	}
}
return 0;
}

/* Timer0 Overflow interrupt service routine */
ISR (__vector_11){ 
	overflows_0++;
}

/* Timer0 Overflow interrupt service routine */
ISR (__vector_5){
	overflows_2++;
}
