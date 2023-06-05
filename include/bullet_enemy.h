#ifndef __BULLET_ENEMY__
#define __BULLET_ENEMY__

#include "struct.h"
#include "const.h"

Bullet_enemy *create_bullet_enemy();
int init_bullets_enemy(Party *party);
int add_bullet_enemy(Party *party, Enemy *enemy);
int move_bullets_enemy(Party *party);
int check_collisions_bullet_enemy(Bullet_enemy *bullet, Player *player);
int enemy_kill_player(Party *party);
int fire_enemy(Party *party);
void free_bullet_enemy(Party *party);

#endif