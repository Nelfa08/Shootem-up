#ifndef __STRUCT__
#define __STRUCT__

#include <MLV/MLV_all.h>
#include "const.h"

/* Structure représentant les différentes entités du jeu */

/* Créer une structure level pour mettre le nbr d'ennemis, leurs vitesse, leur vie, etc et avoir la possibilité de changer en fonction du lvl*/

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
    int delay_shoot;
} Player;

typedef struct bullet_player
{
    Position *position;
    int size;
    int speed;
    int damage;
    int visible;
} Bullet_player;

/* Ajout d'un champ size pour avoir la possibilité de changer la taille de l'enemy*/
typedef struct enemy
{
    Position *position;
    int size;
    int health;
    int speed;
    int visible;
} Enemy;

typedef struct bullet_enemy
{
    Position *position;
    int width;
    int height;
    int speed;
    int damage;
    int visible;
} Bullet_enemy;

typedef struct background
{
    Position *position;
    MLV_Image *image;
} Background;

typedef struct foreground
{
    Position *position;
    MLV_Image *image;
} Foreground;

typedef struct scenery
{
    Background *background;
    Foreground *foreground;
    int speed;
    int scroll;
} Scenery;

typedef struct menu
{
    Background *background;
    MLV_Font *font_text;
    MLV_Font *font_title;
    MLV_Image *img_sound_on;
    MLV_Image *img_sound_off;
} Menu;

typedef int Pressed_key[5];

typedef enum bonus_kind
{
    SHIELD,
    SPEED,
    HEALTH,
    BOMB
} Bonus_kind;

typedef enum penalty_kind
{
    SLOW,
    REVERSE,
    DAMAGE
} Penalty_kind;

typedef struct bonus {
    Position *position;
    Bonus_kind kind;
    int size;
    int speed;
    int visible;
} Bonus;

typedef struct penalty {
    Position *position;
    Penalty_kind kind;
    int size;
    int speed;
    int visible;
} Penalty;

typedef struct party
{
    int state;
    int sound;
    unsigned long int score;
    Player *player;
    Enemy *enemies[MAX_ENEMY];
    Bullet_enemy *bullets_enemy[MAX_BULLET_ENEMY];
    Bullet_player *bullets_player[MAX_BULLET_PLAYER];
    Bonus *bonus[MAX_BONUS];
    Penalty *penalty[MAX_PENALTY];
    Scenery *scenery1;
    Scenery *scenery2;
    Menu *menu;
    Pressed_key pk;
    MLV_Image *image_player;
    MLV_Image *image_heart_full;
    MLV_Image *image_heart_empty;
    MLV_Image *image_bullet_player;
    MLV_Image *image_enemy;
    MLV_Image *image_bullet_enemy;
} Party;

#endif