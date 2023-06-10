/**
 * @file penalty.c
 * @author Corentin RODDIER and Yacine DJEBLOUN
 * @brief File containing all the functions about the penalty
 * @version 1.0
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/const.h"
#include "../include/struct.h"

#include "../include/enemy.h"

#include "../include/penalty.h"

/**
 * @brief Create a penalty object
 *
 * @return Penalty*
 */
Penalty *create_penalty()
{
    Penalty *penalty = malloc(sizeof(Penalty));
    penalty->position = malloc(sizeof(Position));
    penalty->position->x = WIDTH_FRAME_GAME;
    penalty->position->y = 0;
    penalty->size = SIZE_PENALTY;
    penalty->speed = SPEED_PENALTY;
    penalty->visible = 0;

    return penalty;
}

/**
 * @brief add a penalty in array of penalty
 *
 * @param party
 * @return int
 */
int add_penalty(Party *party)
{
    int rand_y = (rand() % (BOTTOM_BORDER - TOP_BORDER + 1)) + TOP_BORDER;
    for (int i = 0; i < MAX_PENALTY; i++)
    {
        if (party->penalty[i]->visible == 0)
        {
            party->penalty[i]->kind = rand() % 3;
            party->penalty[i]->position->x = WIDTH_FRAME_GAME;
            party->penalty[i]->position->y = rand_y;
            party->penalty[i]->visible = 1;
            return 0;
        }
    }
    fprintf(stderr, "Error: No more space for penalty\n");
    return -1;
}

/**
 * @brief init the array of penalty
 *
 * @param party
 */
void init_tab_penalty(Party *party)
{
    party->image_slow_penalty = MLV_load_image(PATH_IMG_SLOW_PENALTY);
    party->image_reverse_penalty = MLV_load_image(PATH_IMG_REVERSE_PENALTY);
    party->sound_reverse_penalty = MLV_load_sound(PATH_SOUND_REVERSE_PENALTY);
    party->image_boss_penalty = MLV_load_image(PATH_IMG_DAMAGE_PENALTY);
    int i;
    for (i = 0; i < MAX_PENALTY; i++)
    {
        party->penalty[i] = create_penalty();
    }
}

/**
 * @brief move the penalty
 *
 * @param party
 */
void move_penalty(Party *party)
{
    for (int i = 0; i < MAX_PENALTY; i++)
    {
        if (party->penalty[i]->visible == 1)
        {
            party->penalty[i]->position->x -= party->penalty[i]->speed;
        }
    }
}

/**
 * @brief check if player collide with a penalty
 *
 * @param party
 * @return int
 */
int collision_penalty(Party *party)
{
    for (int i = 0; i < MAX_PENALTY; i++)
    {
        if (party->penalty[i]->visible == 1)
        {
            if (party->penalty[i]->position->x <= party->player->position->x + party->player->width &&
                party->penalty[i]->position->x + party->penalty[i]->size >= party->player->position->x &&
                party->penalty[i]->position->y <= party->player->position->y + party->player->height &&
                party->penalty[i]->position->y + party->penalty[i]->size >= party->player->position->y)
            {
                party->penalty[i]->visible = 0;
                return i;
            }
        }
    }
    return -1;
}

/**
 * @brief check if player collide with a penalty and apply the penalty effect
 *
 * @param party
 * @return int
 */
int player_get_penalty(Party *party)
{
    int penalty_collision = collision_penalty(party);
    if (penalty_collision != -1)
    {
        if (party->penalty[penalty_collision]->kind == 0)
        {
            if (party->verbose_flag)
            {
                printf("player_get_penalty: SLOW\n");
            }
            if (party->player->speed - 5 >= 5)
            {
                party->player->speed -= 5;
            }
            else
            {
                party->player->speed = 5;
            }
        }
        else if (party->penalty[penalty_collision]->kind == 1)
        {
            if (party->verbose_flag)
            {
                printf("player_get_penalty: REVERSE\n");
            }
            if (party->sound == 1)
            {
                MLV_play_sound(party->sound_reverse_penalty, 1);
            }
            if (party->player->is_reversed == 0)
                party->player->is_reversed = 1;
            else
                party->player->is_reversed = 0;
        }
        else if (party->penalty[penalty_collision]->kind == 2)
        {
            if (party->verbose_flag)
            {
                printf("player_get_penalty: BOSS\n");
            }
            for (int i = 0; i < 10; i++)
            {
                add_enemy(party);
            }
        }
    }
    return 0;
}

void free_penalty(Party *party)
{
    if (party->verbose_flag)
    {
        printf("free_penalty\n");
    }
    MLV_free_image(party->image_reverse_penalty);
    MLV_free_image(party->image_boss_penalty);
    MLV_free_image(party->image_slow_penalty);
    for (int i = 0; i < MAX_BONUS; i++)
    {
        free(party->penalty[i]->position);
        free(party->penalty[i]);
    }
}