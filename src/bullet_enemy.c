/**
 * @file bullet_enemy.c
 * @author Corentin RODDIER and Yacine DJEBLOUN
 * @brief File containing all the functions about the enemy's bullets
 * @version 1.0
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/const.h"
#include "../include/struct.h"

#include "../include/party.h"
#include "../include/bullet_enemy.h"

/**
 * @brief Create a bullet enemy object
 * 
 * @return Bullet_enemy* 
 */
Bullet_enemy *create_bullet_enemy()
{
    Bullet_enemy *bullet = malloc(sizeof(Bullet_enemy));
    bullet->position = malloc(sizeof(Position));
    bullet->position->x = 0;
    bullet->position->y = 0;
    bullet->width = WIDTH_BULLET_ENEMY;
    bullet->height = HEIGHT_BULLET_ENEMY;
    bullet->speed = SPEED_BULLET_ENEMY;
    bullet->damage = DAMAGE_BULLET_ENEMY;
    bullet->visible = 0;
    return bullet;
}

/**
 * @brief Initialize the array of bullets enemy
 * 
 * @param party 
 * @return int 
 */
int init_bullets_enemy(Party *party)
{
    party->image_bullet_enemy = MLV_load_image(PATH_IMG_BULLET_ENEMY);
    int i;
    for (i = 0; i < MAX_BULLET_ENEMY; i++)
    {
        party->bullets_enemy[i] = create_bullet_enemy();
    }
    return 0;
}

/**
 * @brief add a bullet enemy in array of bullets enemy
 * 
 * @param party 
 * @param enemy 
 * @return int 
 */
int add_bullet_enemy(Party *party, Enemy *enemy)
{
    Bullet_enemy *new_bullet = create_bullet_enemy();
    new_bullet->visible = 1;
    new_bullet->position->x = enemy->position->x - new_bullet->width;
    new_bullet->position->y = enemy->position->y + (enemy->height / 4);
    for (int i = 0; i < MAX_BULLET_ENEMY; i++)
    {
        if (party->bullets_enemy[i]->visible == 0)
        {
            party->bullets_enemy[i] = new_bullet;
            return 0;
        }
    }
    fprintf(stderr, "Error: No more space for bullet enemy\n");
    exit(1);
    return 0;
}

/**
 * @brief move the bullets enemy
 * 
 * @param party 
 * @return int 
 */
int move_bullets_enemy(Party *party)
{
    for (int i = 0; i < MAX_BULLET_ENEMY; i++)
    {
        if (party->bullets_enemy[i]->visible == 1)
        {
            party->bullets_enemy[i]->position->x -= party->bullets_enemy[i]->speed;
            if (party->bullets_enemy[i]->position->x < 0)
            {
                party->bullets_enemy[i]->visible = 0;
            }
        }
    }
    return 0;
}

/**
 * @brief check if the bullet enemy is in collision with the player
 * 
 * @param bullet 
 * @param player 
 * @return int 
 */
int check_collisions_bullet_enemy(Bullet_enemy *bullet, Player *player)
{
    if (bullet->position->x <= player->position->x + player->width &&
        bullet->position->x + bullet->width >= player->position->x &&
        bullet->position->y <= player->position->y + player->height &&
        bullet->position->y + bullet->height >= player->position->y)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief decrease the health of the player or the shield when the player is in collision with a bullet enemy 
 * 
 * @param party 
 * @return int 
 */
int enemy_kill_player(Party *party)
{
    for (int i = 0; i < MAX_BULLET_ENEMY; i++)
    {
        if (party->bullets_enemy[i]->visible == 1)
        {
            if (check_collisions_bullet_enemy(party->bullets_enemy[i], party->player) == 1)
            {
                party->bullets_enemy[i]->visible = 0;
                if (party->player->shield == 0)
                {
                    party->player->health -= party->bullets_enemy[i]->damage;
                }
                else
                {
                    party->player->shield -= party->bullets_enemy[i]->damage;
                }
            }
        }
    }
    return 0;
}

/**
 * @brief add a bullet enemy when the enemy shoot
 * 
 * @param party 
 * @return int 
 */
int fire_enemy(Party *party)
{
    int number_enemy = rand() % MAX_ENEMY;
    int rand_shoot = normal_delay(1);
    if (party->enemies[number_enemy]->visible == 1 && rand_shoot < 0.05)
    {
        add_bullet_enemy(party, party->enemies[number_enemy]);
        party->enemies[number_enemy]->status = 1;
    }
    return 0;
}