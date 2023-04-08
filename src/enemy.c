#include "../include/const.h"
#include "../include/struct.h"

#include "../include/enemy.h"

/**
 * @brief Initialisation des ennemies
 *
 * @return Enemy
 */
Enemy *init_enemy()
{
    Enemy *enemy = malloc(sizeof(Enemy));
    enemy->position = malloc(sizeof(Position));
    enemy->position->x = 5;
    enemy->position->y = 4;
    enemy->speed = 5;
    enemy->health = 50;
    enemy->size = 10;
    return enemy;
}