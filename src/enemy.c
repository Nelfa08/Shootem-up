#include <stdlib.h>
#include "../include/const.h"
#include "../include/struct.h"

#include "../include/sprite.h"

#include "../include/enemy.h"

/**
 * @brief Initialisation des ennemies
 *
 * @return Enemy
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
    enemy->height = MLV_get_image_height(party->sprite_walk_enemy->frames[0]);
    enemy->width = MLV_get_image_width(party->sprite_walk_enemy->frames[0]);
    return enemy;
}

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