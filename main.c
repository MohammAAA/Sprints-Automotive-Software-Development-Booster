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

int main()
{
	US_Init(TIMER_0);
	Motor_Init();
	PWM_Init();
	Set_PWM_Prescaling_Value(1024);

	while(1)
	{
		//Schedules the two main function calls with each timer interrupt flag (overflows_2)
 		void Start_Scheduler ()
 		{
 			Check_Distance_Change();

 			if (Ob_Removed==1)
 			{
 					if ((US_Reading >= 200) && (US_Reading <=220))
 					{
 						Get_New_Phase_Info();
 						Ob_Removed = 0;
 					}

 				if ((overflows_0) && (Ob_Removed == 0))
 				{
 					Check_Distance_Change();
 				}

 				if ((overflows_0) && ((US_Reading >= 190) && (US_Reading <=210)))
 				{
 					Get_New_Phase_Info();
 					Ob_Removed = 0;
 				}
 				//Change motor speed according to each phase using Speed_Flag
 				Motor_State (MOTOR_1, FORWARD);
 				Motor_State (MOTOR_2, FORWARD);
 				Motor_Speed_Control(MOTOR_1, Speed_Flag);
 				Motor_Speed_Control(MOTOR_2, Speed_Flag);
 			}
 		}
		Start_Scheduler();

		if (Distance_Front <= 30)
				{
					//stop motor
			Motor_Speed_Control(MOTOR_1,0);
			Motor_Speed_Control(MOTOR_2,0);
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
