#ifndef _GPIO_H_
#define _GPIO_H_
#include <avr/io.h>
#include "MACROS.h"
#include "types.h"

#define PORT__A 0
#define PORT__B 1
#define PORT__C 2
#define PORT__D 3

#define OUTPUT 1
#define INPUT 0

void GPIO_Init(void);
void GPIO_Set_Value(uint8 Port ,uint8 Copy_u8PinNum, uint8 Copy_u8PinValue);
void GPIO_Direction(uint8 PORTx, uint8 nbit, uint8 Direction );



//added
uint8 GPIO_Read(uint8 Port, uint8 PinNum);
void Enable_INT(void);

#endif
