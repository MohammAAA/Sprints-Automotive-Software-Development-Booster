#ifndef TIMERS_H_
#define TIMERS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "types.h"
#define PRE_0 0
#define PRE_1 1
#define PRE_8 8
#define PRE_32 32
#define PRE_64 64
#define PRE_128 128
#define PRE_256 256
#define PRE_1024 1024

#define NO_INT 0
#define CM_INT 1
#define OF_INT 2

//added
#define TIMER_0 0
#define TIMER_2 2

#define OVERFLOW_FLAG 0
#define COMPARE_FLAG 1

#define ONE_SEC 244

void Timer_Set_Prescaler(uint8 Timer_Select, uint16 Timer_Prescaler);
void Timer_init (uint8 Timer_Select, uint8 Interrupt_Activation);
int Timer_read_flags (uint8 Timer_Select, uint8 Flag_ToCheck);

#endif /* TIMERS_H_ */
