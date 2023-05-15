#include <MLV/MLV_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "../include/struct.h"
#include "../include/const.h"
#include "../include/keyboard_listener.h"
#include "../include/sprite.h"

#include "../include/player.h"

/**
 * @brief
 *
 * @return Player
 */
Player *create_player()
{
    Player *player = malloc(sizeof(Player));
    player->position = malloc(sizeof(Position));
    player->position->x = SPAWN_PLAYER_X;
    player->position->y = SPAWN_PLAYER_Y;
    player->health = HEALTH_PLAYER;
    player->speed = SPEED_PLAYER;
    player->delay_shoot = DELAY_SHOOT_PLAYER;
    player->name = "";
    player->shield = 0;
    player->isReversed = 0;
    player->sprite_walk = create_sprite(PLAYER_SPRITE_PATH, NB_FRAMES_PLAYER_WALK, 0);
    player->sprite_attack = create_sprite(PLAYER_SPRITE_PATH, NB_FRAMES_PLAYER_ATTACK, 1);
    player->sprite_dead = create_sprite(PLAYER_SPRITE_PATH, NB_FRAMES_PLAYER_DEAD, 2);
    player->sprite_run = create_sprite(PLAYER_SPRITE_PATH, NB_FRAMES_PLAYER_RUN, 3);
    player->sprite_idle = create_sprite(PLAYER_SPRITE_PATH, NB_FRAMES_PLAYER_IDLE, 4);
    player->height = MLV_get_image_height(player->sprite_walk->frames[0]);
    player->width = MLV_get_image_width(player->sprite_walk->frames[0]);
    
    return player;
}

int move_player(Player *player, Pressed_key pk)
{
    if(player->isReversed == 1){
        for (int i = 0; i < 4; i++)
        {
            pk[i] = pk[i]^1;
        }
        
    }
    if (pk[0] == 1)
    {
        if (player->position->y > TOP_BORDER)
        {
            player->position->y -= player->speed;
        }
        player->sprite_run->status = 1;
    }
    if (pk[1] == 1)
    {
        if ((player->position->x + player->width) < WIDTH_FRAME_GAME)
        {
            player->position->x += player->speed;
        }
        player->sprite_run->status = 1;
    }
    if (pk[2] == 1)
    {
        if ((player->position->y) < BOTTOM_BORDER)
        {
            player->position->y += player->speed;
        }
        player->sprite_run->status = 1;
    }
    if (pk[3] == 1)
    {
        if (player->position->x > 0)
        {
            player->position->x -= player->speed;
        }
    }
    
    if(pk[0] == 0 && pk[1] == 0 && pk[2] == 0)
    {
        player->sprite_run->status = 0;
    }

    return EXIT_SUCCESS;
}

int free_player(Player *player)
{
    free(player->position);
    free(player);
    return EXIT_SUCCESS;
}