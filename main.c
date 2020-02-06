//#include "Phase2_app.h"
#define F_CPU 16000000
#include <avr/delay.h>
#include "Motor.h"
#include "GPIO.h"
#include "types.h"
#include "Motor_types.h"
#include "PWM.h"
#include "US.h"
#include "Timers.h"
#include "ISR.h"

extern volatile uint16 Distance_Front;


void main (void){
	DDRB = 0xFF;
	PORTB = 0x00;
	US_Init(TIMER_0);
	while (1){
		if (Distance_Front < 20){
			PORTB = 0b11110000;
		}
	}


}

/*int main(void)
{
DDRB = 0xFF;
PORTB = 0x00;
// modified its location
Motor_Init();

//added
PWM_Init();
Set_PWM_Prescaling_Value(1024);
US_Init(TIMER_0);


//added
while (1){
Motor_State(MOTOR_1,FORWARD);
Motor_State(MOTOR_2,FORWARD);
Motor_Speed_Control(MOTOR_1,10);
Motor_Speed_Control(MOTOR_2,10);
US_Start(US_FRONT);
if (Distance_Front < 20){
	Motor_State(MOTOR_1,STOP);
	Motor_State(MOTOR_2,STOP);
	PORTB = 0b11110000;
}

}
return 0;
}*/

// 	while(1)
// 	{
// 		//Schedules the two main function calls with each timer interrupt flag (overflows_2) 
// 		void Start_Scheduler ()
// 		{
// 				if ((overflows_2) && (Speed_Perc) && (Ob_Removed == 0))
// 				{
// 					Check_Distance_Change();
// 				}
// 				
// 				if ((overflows_2) && ((US_Reading >= 190) && (US_Reading <=210)) && (Speed_Perc))
// 				{
// 					Get_New_Phase_Info();
// 					Ob_Removed = 0;
// 				}
// 					
// 		}
// 		
// 		//Change motor speed according to each phase using Speed_Flag
// 		Motor_Speed_Control(MOTOR_1,Speed_Flag);
// 		Motor_Speed_Control(MOTOR_2,Speed_Flag);
// 	}
// }
