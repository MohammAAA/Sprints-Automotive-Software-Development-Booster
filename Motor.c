/* This file specifies the functionalities related to the motors operation
** The motors are connected to the most significant portD pins
** the H-bridge controls only two motor signals, so the front and rear motors are connected together in order to adapt to the
** H-brdige constraints
*/

#include "Motor.h"
#include "GPIO.h"
#include "Motor_types.h"


/* This function initializes the motor
** Pre-conditions: None
** Post-conditions: Motors are initialized and ready to operate
** Input arguments: None
** Return: None
*/
void Motor_Init (void)
{
	GPIO_Direction(PORT__D,PIN_1A,OUTPUT);
	GPIO_Direction(PORT__D,PIN_1B,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2A,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2B,OUTPUT);
	GPIO_Direction(PORT__D,PIN_1EN,OUTPUT);
	GPIO_Direction(PORT__D,PIN_2EN,OUTPUT);
}

/* This function specifies the motor state 
** Pre-conditions: motor is initialized
** Post-conditions: Motor direction is specified
** Input arguments: Motor number, motor state whether it is FORWARD or BACKWARD or STOP
** Return: None
*/
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


/* This function controls the motor speed by the use of the PWM 
** Pre-conditions: motor is initialized and its state is defined and updated
** Post-conditions: Motor is operating in the specified direction
** Input arguments: Motor number, speed percentage that the motor will rotate with
** Return: None
*/
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
