#ifndef __WINDOW__
#define __WINDOW__

#include "struct.h"
#include "const.h"


int init_window_menu();
int draw_window_menu(Party *party);
int draw_window_credits(Party *party);
int init_window_game();
int draw_frame_game(Party *party);
int clear_window();
int draw_player(Party *party);
int draw_background(Background *background);
int draw_foreground(Foreground *foreground);
int draw_enemies(Party *party);
int move_scenery(Scenery *scenery1, Scenery *scenery2);
int draw_score(Party *party);
int draw_bullet_player(Party *party);
int draw_health(Party *party);
int draw_bullet_enemy(Party *party);
int draw_loading_screen();
int draw_window_end(Party *party);
int draw_input_name(Party *party);
int draw_bonus(Party *party);
int draw_penalties(Party *party);
int draw_shield(Party *party);
void draw_best_score(Party *party);

#endif