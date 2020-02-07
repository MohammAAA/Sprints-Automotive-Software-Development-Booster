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
			GPIO_Set_Value (PORT__D,PIN_1A,LOW);
			GPIO_Set_Value (PORT__D,PIN_1B,HIGH);
		}
		else{}

		if (BACKWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_1A,HIGH);
			GPIO_Set_Value (PORT__D,PIN_1B,LOW);

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
			GPIO_Set_Value (PORT__D,PIN_2A,LOW);
			GPIO_Set_Value (PORT__D,PIN_2B,HIGH);
		}
		else{}

		if (BACKWARD == Motor_state)
		{
			GPIO_Set_Value (PORT__D,PIN_2A,HIGH);
			GPIO_Set_Value (PORT__D,PIN_2B,LOW);
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
