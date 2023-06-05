/**
 * @file enemy.c
 * @author Corentin RODDIER and Yacine DJEBLOUN
 * @brief File containing all the functions about the enemies
 * @version 1.0
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include "../include/const.h"
#include "../include/struct.h"

#include "../include/sprite.h"

#include "../include/enemy.h"

/**
 * @brief Create a enemy object
 * 
 * @param party 
 * @return Enemy* 
 */
Enemy *create_enemy( Party *party)
{
    Enemy *enemy = malloc(sizeof(Enemy));
    enemy->position = malloc(sizeof(Position));
    enemy->position->x = WIDTH_FRAME_GAME;
    enemy->position->y = 0;
    enemy->health = 1;
    enemy->speed = SPEED_ENEMY;
    enemy->visible = 0;
    enemy->current_frame = 0;
    enemy->status = 0;
    enemy->height = MLV_get_image_height(party->sprite_walk_enemy->frames[0]);
    enemy->width = MLV_get_image_width(party->sprite_walk_enemy->frames[0]);
    return enemy;
}

/**
 * @brief Initialize the array of enemies
 * 
 * @param party 
 */
void init_enemies(Party *party)
{
    int i;
    party->sprite_walk_enemy = create_sprite(ENEMY_SPRITE_PATH, NB_FRAMES_ENEMY_WALK, 0);
    party->sprite_attack_enemy = create_sprite(ENEMY_SPRITE_PATH, NB_FRAMES_ENEMY_ATTACK, 1);
    for (i = 0; i < MAX_ENEMY; i++)
    {
        party->enemies[i] = create_enemy(party);
    }
}

/**
 * @brief add a enemy in array of enemies
 * 
 * @param party 
 * @return int 
 */
int add_enemy(Party *party)
{
    Enemy *new_enemy = create_enemy(party);
    int rand_y = (rand() % (BOTTOM_BORDER - TOP_BORDER + 1)) + TOP_BORDER;

    new_enemy->visible = 1;
    new_enemy->health = (party->score / 500) + 1;
    new_enemy->position->y = rand_y;
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (party->enemies[i]->visible == 0)
        {
            party->enemies[i] = new_enemy;
            return 0;
        }
    }
    fprintf(stderr, "Error: No more space for enemy\n");
    exit(1);
}

/**
 * @brief move all the enemies
 * 
 * @param party 
 * @return int 
 */
int move_enemies(Party *party)
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (party->enemies[i]->visible == 1)
        {
            party->enemies[i]->position->x -= party->enemies[i]->speed;
            if (party->enemies[i]->position->x < -party->enemies[i]->width)
            {
                party->player->health -= 1;
                party->enemies[i]->visible = 0;
            }
        }
    }
    return 0;
}

/**
 * @brief kill all the enemies on the screen
 * 
 * @param party 
 * @return int 
 */
int kill_all_enemies(Party *party)
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        party->enemies[i]->visible = 0;
    }
    return 0;
}

/**
 * @brief free an enemy
 * 
 * @param enemy 
 * @return int 
 */
int free_enemy(Enemy *enemy)
{
    free(enemy->position);
    free(enemy);
    return 0;
}

void free_enemies(Party *party)
{
    printf("free enemies\n");
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        free_enemy(party->enemies[i]);
    }
    free_sprite(party->sprite_walk_enemy);
    free_sprite(party->sprite_attack_enemy);
}
