#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "types.h"

extern uint16 overflows_2;
extern uint16 Speed_Perc;
extern uint8 Ob_Removed;
extern uint16 Speed_Flag;
extern uint16 US_Reading;

uint16 US_Get_Avarage_Reading (void);
void Get_New_Phase_Info(void);
void Check_Distance_Change(void);



#endif /* INCFILE1_H_ */