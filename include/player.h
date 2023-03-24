#ifndef __PLAYER__
#define __PLAYER__

#include "struct.h"
#include "const.h"

Player init_player();
Player move_player(Player player, MLV_Keyboard_button key);
#endif
