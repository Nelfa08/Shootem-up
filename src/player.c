#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"
#include "../include/keyboard_listener.h"

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
    player->size = 100;
    player->speed = 2;
    player->health = 5;
    player->position->x = 0;
    player->position->y = 0;
    player->image = MLV_load_image(PATH_PLAYER);
    return player;
}

Player *move_player(Player *player, Pressed_key pk)
{
    if (pk[0] == 1)
    {
        if (player->position->y > 0)
        {
            player->position->y -= player->speed * 5;
        }
    }
    if (pk[1] == 1)
    {
        if (player->position->x + player->size < WIDTH_FRAME)
        {
            player->position->x += player->speed * 5;
        }
    }
    if (pk[2] == 1)
    {
        if (player->position->y + player->size < HEIGHT_FRAME)
        {
            player->position->y += player->speed * 5;
        }
    }
    if (pk[3] == 1)
    {
        if (player->position->x > 0)
        {
            player->position->x -= player->speed * 5;
        }
    }
    return player;
}