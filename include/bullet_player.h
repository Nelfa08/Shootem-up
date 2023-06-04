#ifndef __BULLET_PLAYER__
#define __BULLET_PLAYER__

#include "struct.h"
#include "const.h"

int init_bullets_player(Party *party);
Bullet_player *create_bullet_player();
int add_bullet_player(Party *party);
int move_bullets_player(Party *party);
int player_kill_ennemy(Party *party);
int check_collisions_bullet_player(Bullet_player *bullet, Enemy *enemy);

#endif
