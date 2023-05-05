#include "../include/struct.h"
#include "../include/const.h"

#include "../include/sprite.h"

Sprite *create_sprite(char *sprite_path, int nb_frames, int kind)
{
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->nb_frames = nb_frames;
    sprite->current_frame = 0;
    sprite->status = 0;
    sprite->frames = malloc(nb_frames * sizeof(MLV_Image *));
    for (int i = 0; i < nb_frames; i++)
    {
        char frame_path[50];
        if (kind == 0)
        {
            sprintf(frame_path, "%s/walk/frame%d.png", sprite_path, i);
            sprite->status = 1;
        }
        else if (kind == 1)
        {
            sprintf(frame_path, "%s/attack/frame%d.png", sprite_path, i);
        }
        else if (kind == 2)
        {
            sprintf(frame_path, "%s/dead/frame%d.png", sprite_path, i);
        }
        else if (kind == 3)
        {
            sprintf(frame_path, "%s/run/frame%d.png", sprite_path, i);
        }
        else if(kind == 4)
        {
            sprintf(frame_path, "%s/idle/frame%d.png", sprite_path, i);
        }
        else
        {
            fprintf(stderr, "Error: invalid kind of sprite\n");
            exit(1);
        }
        sprite->frames[i] = MLV_load_image(frame_path);
    }
    return sprite;
}