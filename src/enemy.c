#include "../include/const.h"
#include "../include/struct.h"

#include "../include/enemy.h"

int init_tab_enemy(Enemy **tab_enemy)
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        Enemy *enemy = malloc(sizeof(Enemy));
        enemy->position = malloc(sizeof(Position));
        enemy->position->x = 0;
        enemy->position->y = 0;
        enemy->speed = SPEED_ENEMY;
        enemy->health = HEALTH_ENEMY;
        enemy->size = SIZE_ENEMY;
        tab_enemy[i] = enemy;
    }
    return 0;
}

/**
 * @brief Initialisation des ennemies
 *
 * @return Enemy
 */
Enemy *create_enemy()
{
    Enemy *enemy = malloc(sizeof(Enemy));
    enemy->position = malloc(sizeof(Position));
    enemy->position->x = 5;
    enemy->position->y = 4;
    enemy->speed = SPEED_ENEMY;
    enemy->health = HEALTH_ENEMY;
    enemy->size = SIZE_ENEMY;
    return enemy;
}

int free_enemy(Enemy *enemy)
{
    free(enemy->position);
    free(enemy);
    return 0;
}