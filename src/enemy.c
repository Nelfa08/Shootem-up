#include "../include/const.h"
#include "../include/struct.h"

/* Revoir les valeurs ici : je les ai mis au hasard*/
Enemy init_enemy() {
    Enemy enemy;
    enemy.health = 50;
    enemy.position.x = 5;
    enemy.position.y = 4;
    enemy.speed = 5;
    enemy.size = 10;
    return enemy;
}