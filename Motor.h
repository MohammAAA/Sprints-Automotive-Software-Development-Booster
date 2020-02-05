#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "types.h"

void Motor_Init (void);
void Motor_State (uint8 Motor_n, uint8 Motor_state);
void Motor_Speed_Control (uint8 Motor_n,uint16 Speed);
void Motor_Turn_Left(void);
void Motor_Turn_Right(void);
void Motor_Move_Forward(void);
//void Motor_Move_Backward(void);

#endif
