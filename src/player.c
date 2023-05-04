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
    player->size = SIZE_PLAYER;
    player->speed = SPEED_PLAYER;
    player->health = HEALTH_PLAYER;
    player->position->x = SPAWN_PLAYER_X;
    player->position->y = SPAWN_PLAYER_Y;
    player->delay_shoot = DELAY_SHOOT_PLAYER;
    player->boost_start_shield = 0;
    return player;
}

int move_player(Player *player, Pressed_key pk)
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
        if ((player->position->y) < BOTTOM_BORDER)
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
    if (player->boost_start_shield != 0)
    {
        if (MLV_get_time() - player->boost_start_shield > TIME_BOOST_SHIELD)
        {
            player->shield = 0;
            player->boost_start_shield = 0;
        }
    }
    return EXIT_SUCCESS;
}

int free_player(Player *player)
{
    free(player->position);
    free(player);
    return EXIT_SUCCESS;
}