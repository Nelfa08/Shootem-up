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
/*
Bonjour à tous,
Petit message pour faire un point sur l'avancé global du serveur.
Initialement, nous avions prévu d'ouvrir le serveur Minecraft le week end qui arrive.
Malheuresement, au vu de l'avancé actuelle, cette ouverture ne sera pas possible.
Honnetement, je suis un peu deg parce que j'y croyais un peu à l'ouverture pour mi-avril, mais on y arrivera pas (tant pis rien de grave)...

C'est pourquoi je vous propose de décaler l'ouverture à fin mai/mi juin max. Je pense que cette période peut etre une très bonne période d'ouverture : beaucoup de jeune vont commencer les vacances donc on va pouvoir ramener pas mal de gens je pense !

Quoiqu'il en soit je trouve que globalement depuis que le serveur s'est remis à travailler, on avance très bien ! Il reste encore pas mal de chose à faire, surtout niveau build, mais globalement je trouve que ca avance très bien !

Encore une fois, je vous remercie tous pour votre implication dans le projet : 

*/