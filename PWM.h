#include "types.h"
#ifndef _PWM_M
#define _PWM_M

#define COM1A0	6
#define COM1A1	7

#define CS10	0
#define CS11	1
#define CS12	2

void PWM_Init(void);
void Set_PWM_Prescaling_Value(uint16 Prescaler);
void SetDutyCycle(uint16 Motor_n , uint16 DutyCycle_perc);



#endif