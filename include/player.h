#ifndef __PLAYER__
#define __PLAYER__

#include "struct.h"
#include "const.h"

Player *create_player();
Player *move_player(Player *player, Pressed_key pk);
#endif
