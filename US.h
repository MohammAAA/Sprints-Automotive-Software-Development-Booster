#ifndef US_H
#define US_H

void US_Init(uint8 Timer_Select);
void US_Start (void);
//uint16 US_Get_Distance (void);

extern volatile uint16 Distance;
extern volatile uint8 int_flag;
extern volatile uint8 flag;
extern volatile uint8 flag_timer;

#define POSITIVE_EDGE 1
#define NEGATIVE_EDGE 0

#endif
