#include "Motor.h"
#include "GPIO.h"
#include "Motor_types.h"

void Motor_Init (void)
{
	GPIO_Direction(PORT__D,PIN_1A,OUTPUT);
	GPIO_Direction(PORT__D,PIN_1B,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2A,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2B,OUTPUT);
	GPIO_Direction(PORT__D,PIN_1EN,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2EN,OUTPUT);
}

void Motor_State (uint8 Motor_n, uint8 Motor_state)
{
	if (MOTOR_1 == Motor_n)
	{
		if (FORWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_1A,HIGH);
			GPIO_Set_Value (PORT__D,PIN_1B,LOW);


		}
		else{}

		if (BACKWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_1A,LOW);
			GPIO_Set_Value (PORT__D,PIN_1B,HIGH);

		}
		else{}

		if (STOP == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_1A,LOW);
			GPIO_Set_Value (PORT__D,PIN_1B,LOW);

		}
		else{}
	}

	if (MOTOR_2 == Motor_n)
	{
		if (FORWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_2A,HIGH);
			GPIO_Set_Value (PORT__D,PIN_2B,LOW);
		}
		else{}

		if (BACKWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_2A,LOW);
			GPIO_Set_Value (PORT__D,PIN_2B,HIGH);
		}
		else{}

		if (STOP == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_2A,LOW);
			GPIO_Set_Value (PORT__D,PIN_2B,LOW);
		}
		else{}

	}
}

void Motor_Turn_Left()
{
// assuming motor 1 is on the left side

	Motor_State (MOTOR_1, STOP);
	Motor_State (MOTOR_2, FORWARD);
	Motor_Speed_Control (MOTOR_1, MAX_SPEED);
	Motor_Speed_Control (MOTOR_2, MAX_SPEED);



}
	
void Motor_Turn_Right()
{
	Motor_State (MOTOR_1, FORWARD);
	Motor_State (MOTOR_2, STOP);
	Motor_Speed_Control (MOTOR_1, MAX_SPEED);
	Motor_Speed_Control (MOTOR_2, MAX_SPEED);

}

void Motor_Speed_Control (uint8 Motor_n, uint16 Speed)
{
	if (MAX_SPEED == Speed)
	{
		if (MOTOR_1 == Motor_n)
		{
			GPIO_Set_Value (PORT__D,PIN_1EN,HIGH);
		}
		else{}

		if (MOTOR_2 == Motor_n)
		{
			GPIO_Set_Value (PORT__D,PIN_2EN,HIGH);
		}
		else {}
	}
	else{}
}

