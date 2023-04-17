#ifndef __STRUCT__
#define __STRUCT__

#include <MLV/MLV_all.h>

/* Structure représentant les différentes entités du jeu */

/* Créer une structure level pour mettre le nbr d'ennemis, leurs vitesse, leur vie, etc et avoir la possibilité de changer en fonction du lvl*/
typedef struct party {
    int state;
} Party;

typedef struct position
{
    int x;
    int y;
} Position;

typedef struct player
{
    Position *position;
    int size;
    int health;
    int speed;
    MLV_Image *image;
} Player;

typedef struct bullet_player
{
    Position *position;
    int size;
    int speed;
    int damage;
} Bullet_player;

/* Ajout d'un champ size pour avoir la possibilité de changer la taille de l'ennemy*/
typedef struct enemy
{
    Position *position;
    int size;
    int health;
    int speed;
    MLV_Image *image;
} Enemy;

typedef struct bullet_enemy
{
    Position *position;
    int size;
    int speed;
    int damage;
} Bullet_enemy;

typedef struct background
{
    Position *position;
    char *path;
} Background;


typedef int Pressed_key[4];

#endif