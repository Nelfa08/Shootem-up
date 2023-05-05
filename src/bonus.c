#include "../include/const.h"
#include "../include/struct.h"

#include "../include/enemy.h"
#include "../include/bonus.h"

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

int add_bonus(Party *party)
{
    printf("add_bonus\n");
    Bonus *new_bonus = create_bonus();
    int rand_y = (rand() % (BOTTOM_BORDER - TOP_BORDER + 1)) + TOP_BORDER;
    new_bonus->visible = 1;
    new_bonus->position->y = rand_y;
    // new_bonus->kind = rand() % 4;
    new_bonus->kind = 0;
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

void init_tab_bonus(Party *party)
{
    int i;
    for (i = 0; i < MAX_BONUS; i++)
    {
        party->bonus[i] = create_bonus();
    }
}

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
        }
        return 1;
    }
    return 0;
}