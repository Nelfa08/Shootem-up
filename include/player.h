#ifndef __PLAYER__
#define __PLAYER__

#include "struct.h"
#include "const.h"

Player *create_player();
int move_player(Player *player, Pressed_key pk);
int free_player(Player *player);
#endif
