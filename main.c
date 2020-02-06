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



int main(void)
{
// modified
Motor_Init();
//added
while (1){
Motor_State(MOTOR_1,FORWARD);
Motor_State(MOTOR_2,FORWARD);
	Motor_Speed_Control(MOTOR_1,100);
	Motor_Speed_Control(MOTOR_2,100);
}
return 0;
}

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
