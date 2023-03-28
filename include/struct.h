#ifndef __STRUCT__
#define __STRUCT__

#include <MLV/MLV_all.h>

/* Structure représentant les différentes entités du jeu */

typedef struct
{
    int x;
    int y;
} Position;

typedef struct
{
    Position position;
    int size;
    int health;
    int speed;
    char *path;
} Player;

/* Ajout d'un champ size pour avoir la possibilité de changer la taille de l'ennemy*/
typedef struct
{
    Position position;
    int size;
    int health;
    int speed;
} Enemy;

typedef struct
{
    Position position;
    int size;
    int speed;
    int damage;
} Bullet_player;

typedef struct
{
    Position position;
    char *path;
} Background;

typedef int Pressed_key[4];

#endif