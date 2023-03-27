#ifndef __PLAYER__
#define __PLAYER__

#include "struct.h"
#include "const.h"

Player init_player();
int detect_key_pressed(Pressed_key pk);
void init_pressed_key(Pressed_key pk);
Player move_player(Player player, Pressed_key pk);

#endif
