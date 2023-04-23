#ifndef __ENEMY__
#define __ENEMY__

#include "struct.h"
#include "const.h"

void init_tab_enemy(Party *party);
Enemy *create_enemy();
int free_enemy(Enemy *enemy);
int add_enemy(Enemy **enemies);
Enemy *init_enemy();
int move_enemies(Enemy **enemies);
int print_enemies(Enemy **enemies);

#endif
