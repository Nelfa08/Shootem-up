#include "../include/const.h"
#include "../include/struct.h"

#include "../include/bullet_player.h"

Bullet_player *create_bullet_player()
{
    Bullet_player *bullet = malloc(sizeof(Bullet_player));
    bullet->position = malloc(sizeof(Position));
    bullet->position->x = 0;
    bullet->position->y = 0;
    bullet->size = SIZE_BULLET_PLAYER;
    bullet->speed = SPEED_BULLET_PLAYER;
    bullet->damage = DAMAGE_BULLET_PLAYER;
    bullet->visible = 0;
    return bullet;
}

int init_bullets_player(Party *party)
{
    int i;
    for (i = 0; i < MAX_BULLET_PLAYER; i++)
    {
        party->bullets_player[i] = create_bullet_player();
    }
    return 0;
}

int add_bullet_player(Party *party)
{
    Bullet_player *new_bullet = create_bullet_player();
    new_bullet->visible = 1;
    new_bullet->position->x = party->player->position->x + party->player->size;
    new_bullet->position->y = party->player->position->y + (party->player->size / 4);
    for (int i = 0; i < MAX_BULLET_PLAYER; i++)
    {
        if (party->bullets_player[i]->visible == 0)
        {
            party->bullets_player[i] = new_bullet;
            return 0;
        }
    }
    fprintf(stderr, "Error: No more space for bullet player\n");
    exit(1);
}

int print_bullets_player(Party *party)
{
    printf("[ ");
    for (int i = 0; i < MAX_BULLET_PLAYER; i++)
    {
        printf("%d ", party->bullets_player[i]->visible);
    }
    printf(" ]\n");
    return 0;
}

int move_bullets_player(Party *party)
{
    for (int i = 0; i < MAX_BULLET_PLAYER; i++)
    {
        if (party->bullets_player[i]->visible == 1)
        {
            party->bullets_player[i]->position->x += party->bullets_player[i]->speed;
            if (party->bullets_player[i]->position->x > WIDTH_FRAME_GAME)
            {
                party->bullets_player[i]->visible = 0;
            }
        }
    }
    return 0;
}

int collision_bullets_player(Party *party)
{
    for (int i = 0; i < MAX_BULLET_PLAYER; i++)
    {
        if (party->bullets_player[i]->visible == 1)
        {
            for (int j = 0; j < MAX_ENEMY; j++)
            {
                if (party->enemies[j]->visible == 1)
                {
                    if (party->bullets_player[i]->position->x + party->bullets_player[i]->size >= party->enemies[j]->position->x &&
                        party->bullets_player[i]->position->x <= party->enemies[j]->position->x + party->enemies[j]->size &&
                        party->bullets_player[i]->position->y + party->bullets_player[i]->size >= party->enemies[j]->position->y &&
                        party->bullets_player[i]->position->y <= party->enemies[j]->position->y + party->enemies[j]->size)
                    {
                        party->bullets_player[i]->visible = 0;
                        party->enemies[j]->visible = 0;
                    }
                }
            }
        }
    }
    return 0;
}