/**
 * @file bonus.c
 * @author Corentin RODDIER and Yacine DJEBLOUN
 * @brief File containing all the functions about the bonus
 * @version 1.0
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/const.h"
#include "../include/struct.h"

#include "../include/enemy.h"
#include "../include/bonus.h"

/**
 * @brief Create a bonus object
 * 
 * @return Bonus*
 */
Bonus *create_bonus()
{
    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->position = malloc(sizeof(Position));
    bonus->position->x = WIDTH_FRAME_GAME;
    bonus->position->y = 0;
    bonus->size = SIZE_BONUS;
    bonus->speed = SPEED_BONUS;
    bonus->visible = 0;

    return bonus;
}

/**
 * @brief add a bonus in array of bonus
 * 
 * @param party 
 * @return int 
 */
int add_bonus(Party *party)
{
    Bonus *new_bonus = create_bonus();
    int rand_y = (rand() % (BOTTOM_BORDER - TOP_BORDER + 1)) + TOP_BORDER;
    new_bonus->visible = 1;
    new_bonus->position->y = rand_y;
    new_bonus->kind = rand() % 5;
    for (int i = 0; i < MAX_BONUS; i++)
    {
        if (party->bonus[i]->visible == 0)
        {
            party->bonus[i] = new_bonus;
            return 0;
        }
    }
    fprintf(stderr, "Error: No more space for bonus\n");
    exit(1);
}

/**
 * @brief init the array of bonus
 * 
 * @param party 
 */
void init_tab_bonus(Party *party)
{
    party->image_shield_bonus = MLV_load_image(PATH_IMG_SHIELD_BONUS);
    party->image_speed_bonus = MLV_load_image(PATH_IMG_SPEED_BONUS);
    party->image_health_bonus = MLV_load_image(PATH_IMG_HEALTH_BONUS);
    party->image_bomb_bonus = MLV_load_image(PATH_IMG_BOMB_BONUS);
    party->sound_bomb_bonus = MLV_load_sound("data/music/bomb.wav");
    party->image_attack_bonus = MLV_load_image(PATH_IMG_ATTACK_BONUS);
    for (int i = 0; i < MAX_BONUS; i++)
    {
        party->bonus[i] = create_bonus();
    }
}

/**
 * @brief move the bonus if it's visible
 * 
 * @param party 
 */
void move_bonus(Party *party)
{
    for (int i = 0; i < MAX_BONUS; i++)
    {
        if (party->bonus[i]->visible == 1)
        {
            party->bonus[i]->position->x -= party->bonus[i]->speed;
        }
    }
}

/**
 * @brief check if player collide with a bonus
 * 
 * @param party 
 * @return int 
 */
int collision_bonus(Party *party)
{
    for (int i = 0; i < MAX_BONUS; i++)
    {
        if (party->bonus[i]->visible == 1)
        {
            if (party->bonus[i]->position->x <= party->player->position->x + party->player->width &&
                party->bonus[i]->position->x + party->bonus[i]->size >= party->player->position->x &&
                party->bonus[i]->position->y <= party->player->position->y + party->player->height &&
                party->bonus[i]->position->y + party->bonus[i]->size >= party->player->position->y)
            {
                party->bonus[i]->visible = 0;
                return i;
            }
        }
    }
    return -1;
}

/**
 * @brief add effect of bonus to player 
 * 
 * @param party 
 * @return int 
 */
int player_get_bonus(Party *party)
{
    int bonus_collision = collision_bonus(party);
    if (bonus_collision != -1)
    {
        if (party->bonus[bonus_collision]->kind == 0)
        {
            printf("player_win_bonus: SHIELD\n");
            party->player->shield = 3;
        }
        else if (party->bonus[bonus_collision]->kind == 1)
        {
            printf("player_win_bonus: SPEED\n");
            if (party->player->speed < 20)
            {
                party->player->speed += 2;
            }
        }
        else if (party->bonus[bonus_collision]->kind == 2)
        {
            printf("player_win_bonus: HEALTH\n");
            if (party->player->health < 3)
            {
                party->player->health += 1;
            }
        }
        else if (party->bonus[bonus_collision]->kind == 3)
        {
            printf("player_win_bonus: BOMB\n");
            kill_all_enemies(party);
            if (party->sound == 1)
            {
                MLV_play_sound(party->sound_bomb_bonus, 1);
            }
        }
        else if (party->bonus[bonus_collision]->kind == 4)
        {
            printf("player_win_bonus: ATTACK\n");
            for (int i = 0; i < MAX_BULLET_PLAYER; i++)
            {
                party->bullets_player[i]->damage += 1;
            }
        }
        return 1;
    }
    return 0;
}

void free_bonus(Party *party)
{
    if(party->verbose_flag)
    {
        printf("free_bonus\n");
    }
    MLV_free_image(party->image_shield_bonus);
    MLV_free_image(party->image_speed_bonus);
    MLV_free_image(party->image_health_bonus);
    MLV_free_image(party->image_bomb_bonus);
    MLV_free_image(party->image_attack_bonus);
    MLV_free_sound(party->sound_bomb_bonus);
    for (int i = 0; i < MAX_BONUS; i++)
    {
        free(party->bonus[i]->position);
        free(party->bonus[i]);
    }
}