#ifndef __ENEMY__
#define __ENEMY__

#include "struct.h"
#include "const.h"

void init_enemies(Party *party);
Enemy *create_enemy(Party *party);
int free_enemy(Enemy *enemy);
int add_enemy(Party *party);
int move_enemies(Party *party);
int kill_all_enemies(Party *party);

#endif
