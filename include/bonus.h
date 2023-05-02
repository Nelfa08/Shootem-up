#ifndef __BONUS__
#define __BONUS__

#include "struct.h"
#include "const.h"

void init_tab_bonus(Party *party);
Bonus *create_bonus();
int add_bonus(Party *party);
void move_bonus(Party *party);
int collision_bonus(Party *party);
int player_get_bonus(Party *party);

#endif
