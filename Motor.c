#include "Motor.h"
#include "GPIO.h"
#include "Motor_types.h"
#include "PWM.h"


//intialize the motor pins in PORTD as Output
void Motor_Init (void)
{
	GPIO_Direction(PORT__D,PIN_1A,OUTPUT);
	GPIO_Direction(PORT__D,PIN_1B,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2A,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2B,OUTPUT);
	GPIO_Direction(PORT__D,PIN_1EN,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2EN,OUTPUT);

	//added
	GPIO_Set_Value (PORT__D,PIN_1EN,HIGH);
	GPIO_Set_Value (PORT__D,PIN_2EN,HIGH);
}

// change motor1/motor2 states to one of those
// ( Forward and Backward directions , OFF )
void Motor_State (uint8 Motor_n, uint8 Motor_state)
{
	if (MOTOR_1 == Motor_n)
	{
		if (FORWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_1A,HIGH);
			GPIO_Set_Value (PORT__D,PIN_1B,LOW);
		}

		if (BACKWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_1A,LOW);
			GPIO_Set_Value (PORT__D,PIN_1B,HIGH);

		}

		if (STOP == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_1A,LOW);
			GPIO_Set_Value (PORT__D,PIN_1B,LOW);

		}
	}
		
	if (MOTOR_2 == Motor_n)
	{
		if (FORWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_2A,HIGH);
			GPIO_Set_Value (PORT__D,PIN_2B,LOW);
		}
		
		if (BACKWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_2A,LOW);
			GPIO_Set_Value (PORT__D,PIN_2B,HIGH);
		}
		
		if (STOP == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_2A,LOW);
			GPIO_Set_Value (PORT__D,PIN_2B,LOW);
		}
	}
}

//change the Speed Percentage, relative to the total speed of the motor
void Motor_Speed_Control (uint8 Motor_n, uint16 Speed_Perc)
{
		if (MOTOR_1 == Motor_n)
		{
			 SetDutyCycle(MOTOR_1,Speed_Perc);
		}
		if (MOTOR_2 == Motor_n)
		{
			 SetDutyCycle(MOTOR_2,Speed_Perc);
		}
}
