#ifndef __WINDOW__
#define __WINDOW__

#include "struct.h"
#include "const.h"


int init_window_menu();
int draw_window_menu();
int draw_window_credits();
int init_window_game();
int draw_frame_game(Player *player);
int clear_window();
int free_window();

#endif