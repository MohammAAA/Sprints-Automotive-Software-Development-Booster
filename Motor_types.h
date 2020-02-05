/*
 * Motor_types.h
 *
 *  Created on: Feb 2, 2020
 *      Author: rimo
 */

#ifndef MOTOR_TYPES_H_
#define MOTOR_TYPES_H_

#define FORWARD 1
#define BACKWARD 2
#define STOP 3

#define MOTOR_1 1
#define MOTOR_2 2

#define PIN_1A	2
#define PIN_1B	3
#define PIN_1EN	4
#define PIN_2EN	5
#define PIN_2A	6
#define PIN_2B	7

#define MAX_SPEED 255

void Motor_Init (void);
void Motor_State (uint8 Motor_n, uint8 Motor_state);
void Motor_Speed_Control (uint8 Motor_n, uint16 Speed);
void Motor_Turn_Left(void);
void Motor_Turn_Right(void);
void Motor_Move_Forward(void);
void Motor_Move_Backward(void);





#endif /* MOTOR_TYPES_H_ */
