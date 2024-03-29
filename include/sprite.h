#ifndef __SPRITE__
#define __SPRITE__

#include "struct.h"
#include "const.h"

Sprite *create_sprite(char *sprite_path, int nb_frames, int kind);
void free_sprite(Sprite *sprite, int verbose_flag);
#endif