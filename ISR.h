#ifndef ISR_H_
#define ISR_H_

#include "types.h"
#include "Timers.h"
#include "US.h"
#include "avr/interrupt.h"

extern volatile uint16 Distance;

// ISR (__vector_3); //PB2 (for Ultrasonic)
// ISR (__vector_5); //Timer2
// ISR (__vector_11); //Timer0

#endif /* ISR_H_ */