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
    player->speed = SPEED_PLAYER;
    player->health = HEALTH_PLAYER;
    player->position->x = SPAWN_PLAYER_X;
    player->position->y = SPAWN_PLAYER_Y;
    player->image = MLV_load_image(PATH_PLAYER);
    return player;
}

Player *move_player(Player *player, Pressed_key pk)
{
    if (pk[0] == 1)
    {
        if (player->position->y > TOP_BORDER)
        {
            player->position->y -= player->speed;
        }
    }
    if (pk[1] == 1)
    {
        if ((player->position->x + player->size) < WIDTH_FRAME_GAME)
        {
            player->position->x += player->speed;
        }
    }
    if (pk[2] == 1)
    {
        if ((player->position->y + player->size) < BOTTOM_BORDER)
        {
            player->position->y += player->speed;
        }
    }
    if (pk[3] == 1)
    {
        if (player->position->x > 0)
        {
            player->position->x -= player->speed;
        }
    }
    return player;
}

int free_player(Player *player)
{
    free(player->position);
    MLV_free_image(player->image);
    free(player);
    return EXIT_SUCCESS;
}