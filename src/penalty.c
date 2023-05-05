#include "../include/const.h"
#include "../include/struct.h"

#include "../include/penalty.h"

Penalty *create_penalty()
{
    Penalty *penalty = malloc(sizeof(Penalty));
    penalty->position = malloc(sizeof(Position));
    penalty->position->x = WIDTH_FRAME_GAME;
    penalty->position->y = 0;
    penalty->size = SIZE_PENALTY;
    penalty->speed = SPEED_PENALTY;
    penalty->visible = 0;

    return penalty;
}

int add_penalty(Party *party)
{
    printf("add_penalty\n");
    Penalty *new_penalty = create_penalty();
    int rand_y = (rand() % (BOTTOM_BORDER - TOP_BORDER + 1)) + TOP_BORDER;
    new_penalty->visible = 1;
    new_penalty->position->y = rand_y;
    new_penalty->kind = rand() % 3;
    for (int i = 0; i < MAX_PENALTY; i++)
    {
        if (party->penalty[i]->visible == 0)
        {
            party->penalty[i] = new_penalty;
            return 0;
        }
    }
    fprintf(stderr, "Error: No more space for penalty\n");
    exit(1);
}

void init_tab_penalty(Party *party)
{
    int i;
    for (i = 0; i < MAX_PENALTY; i++)
    {
        party->penalty[i] = create_penalty();
    }
}


void move_penalty(Party *party)
{
    for (int i = 0; i < MAX_PENALTY; i++)
    {
        if (party->penalty[i]->visible == 1)
        {
            party->penalty[i]->position->x -= party->penalty[i]->speed;
        }
    }
}

int collision_penalty(Party *party)
{
    for (int i = 0; i < MAX_PENALTY; i++)
    {
        if (party->penalty[i]->visible == 1)
        {
            if (party->penalty[i]->position->x <= party->player->position->x + party->player->width &&
                party->penalty[i]->position->x + party->penalty[i]->size >= party->player->position->x &&
                party->penalty[i]->position->y <= party->player->position->y + party->player->height &&
                party->penalty[i]->position->y + party->penalty[i]->size >= party->player->position->y)
            {
                party->penalty[i]->visible = 0;
                return i;
            }
        }
    }
    return -1;
}

int player_get_penalty(Party *party)
{
    int penalty_collision = collision_penalty(party);
    if (penalty_collision != -1)
    {
        if (party->penalty[penalty_collision]->kind == 0)
        {
            printf("player_get_penalty: SLOW\n");
            if(party->player->speed > 5) {
                party->player->speed -= 5;
            }
        }
        else if (party->penalty[penalty_collision]->kind == 1)
        {
            printf("player_get_penalty: REVERSE\n");
        }
        else if (party->penalty[penalty_collision]->kind == 2)
        {
            printf("player_get_penalty: DAMAGE\n");
            party->player->health -= 1;
        }
    }
    return 0;
}