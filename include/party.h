#ifndef __PARTY__
#define __PARTY__

#include "struct.h"

Party *init_party(int verbose_flag, int hitbox_flag);
double normal_delay(double mean);
int free_party(Party *party);
int read_scoreboard(Party *party);
void generate_bonus_or_penalty(Party *party);
int write_scoreboard(Party *party);
int sort_scoreboard(Party *party);
int read_scoreboard(Party *party);
int print_scoreboard(Party *party);
int insert_scoreboard(Party *party);
int init_img_loading(MLV_Image *loading_images[]);
int init_scenery(Party *party, MLV_Image *loading_images[]);
int init_menu(Party *party);
int init_scoreboard(Party *party);

#endif