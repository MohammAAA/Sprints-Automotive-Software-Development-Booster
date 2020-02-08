/* This file defines the needed Macros in the project */

#ifndef _MACROS_H_
#define _MACROS_H_

#define SETBIT(REG,NBIT) (REG|=(1<<NBIT))
#define CLRBIT(REG,NBIT) (REG&=~(1<<NBIT))
#define TOGGLEBIT(REG,NBIT) (REG^=(1<<NBIT))
#define BIT_IS_SET(REG,NBIT) (REG&=(1<<NBIT))
#define BIT_IS_CLEAR(REG,NBIT) (!(REG&=(1<<NBIT)))
#define GET_BIT(REG, NBIT)	((REG >> NBIT) & 1)

#endif
