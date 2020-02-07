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


extern volatile uint16 Distance ;
extern volatile uint16 overflows_0;
extern volatile uint16 overflows_2;


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
int main()
{
	US_Init(TIMER_0);
	//Timer_Set_Prescaler(TIMER_0, PRE_256);

	Motor_Init();
	PWM_Init();
	Set_PWM_Prescaling_Value(1024);

	while(1)
	{

					/* Motor_State (MOTOR_1, FORWARD);
					Motor_State (MOTOR_2, FORWARD);

					Motor_Speed_Control(MOTOR_1,10);
					Motor_Speed_Control(MOTOR_2,10); */
		//Schedules the two main function calls with each timer interrupt flag (overflows_2)
 		void Start_Scheduler ()
 		{
 		/*	Motor_State (MOTOR_1, FORWARD);
 			Motor_State (MOTOR_2, FORWARD);
			Motor_Speed_Control(MOTOR_1,10);
			Motor_Speed_Control(MOTOR_2,10); */
 			Check_Distance_Change();

 			/* Motor_State (MOTOR_1, FORWARD);
 			Motor_State (MOTOR_2, FORWARD);
			Motor_Speed_Control(MOTOR_1,50);
			Motor_Speed_Control(MOTOR_2,50); */
// 			
 			if (Ob_Removed==1)
 			{
 					if ((US_Reading >= 200) && (US_Reading <=220))
 					{
 						Get_New_Phase_Info();
 						Ob_Removed = 0;
 					}
// 				
 			//()(_)}
// 				
 		//()(_)}

			/* Motor_State (MOTOR_1, FORWARD);
			Motor_State (MOTOR_2, FORWARD);

			Motor_Speed_Control(MOTOR_1,90);
			Motor_Speed_Control(MOTOR_2,90); */
	//*}
//*}
 				if ((overflows_0) /*&& (Speed_Perc)*/ && (Ob_Removed == 0))
 				{
 					Check_Distance_Change();
 				}
// 
 				if ((overflows_0) && ((US_Reading >= 190) && (US_Reading <=210)) /*&& (Speed_Perc)*/)
 				{
 					Get_New_Phase_Info();
 					Ob_Removed = 0;
 				}

 				Motor_State (MOTOR_1, FORWARD);
 				Motor_State (MOTOR_2, FORWARD);

 				Motor_Speed_Control(MOTOR_1, 30 /*Speed_Flag*/);
 				Motor_Speed_Control(MOTOR_2, 30	 /*10Speed_Flag*/);
 			}
 		}
		Start_Scheduler();

		if (Distance <= 20)
				{
					//stop motor
			Motor_Speed_Control(MOTOR_1,0);
			Motor_Speed_Control(MOTOR_2,0);				}

	}
}

		//Change motor speed according to each phase using Speed_Flag





// int main (void)
// {
// 
// // phase 1 //
// 
// //	Motor_Init();
// 
// 	//Motor_State(MOTOR_1,FORWARD);
// 	/*Motor_Speed_Control(MOTOR_1,MAX_SPEED);
// 
// 	Motor_State(MOTOR_2,FORWARD);
// 	Motor_Speed_Control(MOTOR_2,MAX_SPEED);*/
// 
// 
// // phase 2 //
// 
// //*************************************************UltraSonic Sensor*******************************************************
// 
// 										//SETBIT(PORTB,2);
// 										//_delay_us(10);
// 										//CLRBIT(PORTB,2);
// 
// 										//DDRB=0b11111011;
// 										//PORTB = 0x00;
// //PORTB = 0b11111011;
// //_delay_ms(1000);
// 
// US_Init(TIMER_0);
// //Timer_Set_Prescaler(TIMER_0, PRE_256);
// 
// Motor_Init();
// PWM_Init();
// Set_PWM_Prescaling_Value(1);
// 
// 
// 
// while(1)
// {
// 	US_Start();
// 
// 
// 
// 	if (Distance < 20)
// 	{	
// 				Motor_State (MOTOR_1, STOP);
// 				Motor_State (MOTOR_2, STOP);
// 	}
// 	else
// 	{
// 
// 		PORTB = 0b10000000;
// 		Motor_State (MOTOR_1, FORWARD);
// 		Motor_State (MOTOR_2, FORWARD);
// 	//	PWM_Init(0);
// 
// 		Motor_Speed_Control (MOTOR_1, 100);
// 		Motor_Speed_Control (MOTOR_2, 80);
// 
// 		
// 		//_delay_ms(2000);
// 	}
// }
// 
// 
// 
// return 0;
// }



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
