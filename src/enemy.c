#include "../include/const.h"
#include "../include/struct.h"

/**
 * @brief Initialisation des ennemies
 * 
 * @return Enemy 
 */
Enemy init_enemy() {
    Enemy enemy;
    enemy.health = 50;
    enemy.position.x = 5;
    enemy.position.y = 4;
    enemy.speed = 5;
    enemy.size = 10;
    return enemy;
}