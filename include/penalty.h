#ifndef __PENALTY__
#define __PENALTY__

#include "struct.h"
#include "const.h"

Penalty *create_penalty(); 
void init_tab_penalty(Party *party);
int add_penalty(Party *party);
void move_penalty(Party *party);


#endif
