#include <stdlib.h>
#include "../include/const.h"
#include "../include/struct.h"

#include "../include/enemy.h"

Enemy *init_enemy()
{
    Enemy *enemy = malloc(sizeof(Enemy));
    enemy->position = malloc(sizeof(Position));
    enemy->position->x = 0;
    enemy->position->y = 0;
    enemy->speed = SPEED_ENEMY;
    enemy->health = HEALTH_ENEMY;
    enemy->size = SIZE_ENEMY;
    return enemy;
}

void init_tab_enemy(Party *party)
{
    int i;
    for (i = 0; i < MAX_ENEMY; i++)
    {
        party->enemies[i] = init_enemy();
    }
}

/**
 * @brief Initialisation des ennemies
 *
 * @return Enemy
 */
Enemy *create_enemy()
{
    int rand_y = (rand() % (BOTTOM_BORDER - TOP_BORDER + 1)) + TOP_BORDER;
    Enemy *enemy = malloc(sizeof(Enemy));
    enemy->position = malloc(sizeof(Position));
    enemy->position->x = WIDTH_FRAME_GAME;
    enemy->position->y = rand_y;
    enemy->speed = SPEED_ENEMY;
    enemy->health = HEALTH_ENEMY;
    enemy->size = SIZE_ENEMY;
    return enemy;
}

int add_enemy(Party *party)
{
    Enemy *new_enemy = create_enemy();
    new_enemy->visible = 1;
    new_enemy->health = (party->score / 500) + 1;
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

int move_enemies(Party *party)
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (party->enemies[i]->visible == 1)
        {
            party->enemies[i]->position->x -= party->enemies[i]->speed;
            if (party->enemies[i]->position->x < -party->enemies[i]->size)
            {
                party->player->health -= 1;
                party->enemies[i]->visible = 0;
            }
        }
    }
    return 0;
}

int print_enemies(Enemy **enemies)
{
    printf("[");
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        printf("%d, ", enemies[i]->visible);
    }
    printf("]\n");
    return 0;
}

int kill_all_enemies(Party *party)
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        party->enemies[i]->visible = 0;
    }
    return 0;
}

int free_enemy(Enemy *enemy)
{
    free(enemy->position);
    free(enemy);
    return 0;
}