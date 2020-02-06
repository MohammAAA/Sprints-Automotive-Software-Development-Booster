#include "Phase2_app.h"

uint16 Total_Distance	= 600;
uint16 Covered_Distance = 0;
uint16 First_Reading	= 200;
uint16 New_Reading		= 0;
uint16 Rem_Distance		= 600;
uint16 Speed_Flag		= 0;
uint8 Ob_Removed		= 0;
uint16 Total_Reading	= 0;
uint16 Avarage_Reading	= 0;
uint16 US_Reading		= 0;
extern volatile uint16 Distance;

/*
	Requests two readings from Ultrasonic then return the avarage
*/
uint16 US_Get_Avarage_Reading (void)
{
	Total_Reading = 0;
	for (uint16 i=0;i<2;i++)
	{
		//int this function it must not return untill interrupt flag is available and value is ready
		//if synchronous then a return value is given
		US_Start();
		
		New_Reading = Distance;
		Total_Reading += New_Reading;
		Avarage_Reading = Total_Reading/i;
	}
	return Avarage_Reading;
}

/*
	info about the start start of each phase
	First_Reading:	distance to the next obstacle
	Total_Distance:	distance to the end of the track
	eg. first phase -> First_reading = 200, Total_Distance = 600
*/
void Get_New_Phase_Info(void)
{
	First_Reading = Distance;
			
	if (Total_Distance == 400)
	{
		Total_Distance = 200;
	}
			
	if (Total_Distance == 600)
	{
		Total_Distance = 400;
	}
}

/*
	Calculate Remaining Distance (Rem_Distance)
	assigning the proportional speed to a flag (Speed_Flag)
*/
void Check_Distance_Change(void)
{
	US_Reading = Distance;
	// neglecting the effect of obstacle removal
	if (US_Reading >= 200)
	{
		US_Reading = US_Reading - 200;
		Ob_Removed = 1;
	}
	

	Covered_Distance = First_Reading - US_Reading;
	Rem_Distance = Total_Distance - Covered_Distance;
	
	if ((Rem_Distance > 400) && (Rem_Distance <= 600))
	{
		//move with 30% Speed
		Speed_Flag = 30;
	}
	
	if ((Rem_Distance > 200) && (Rem_Distance <= 400))
	{
		//move with 60% Speed
		Speed_Flag = 60;
	}
	
	if ((Rem_Distance > 0) && (Rem_Distance <= 200))
	{
		if (Rem_Distance <= 20)
		{
			//stop motor
			Speed_Flag = 0;
		}
		
		else
		{
			//move with 90% Speed
			Speed_Flag = 90;
		}
	}
}
