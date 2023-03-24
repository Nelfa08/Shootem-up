#ifndef __STRUCT__
#define __STRUCT__

/* Structure représentant les différentes entités du jeu */

typedef struct position
{
    int x;
    int y;
} Position;

typedef struct player
{
    Position position;
    int size;
    int health;
    int speed;
} Player;

/* Ajout d'un champ size pour avoir la possibilité de changer la taille de l'ennemy*/
typedef struct enemy
{
    Position position;
    int size;
    int health;
    int speed;
} Enemy;

typedef struct bullet_player
{
    Position position;
    int size;
    int speed;
    int damage;
} Bullet_player;

#endif