#ifndef __STRUCT__
#define __STRUCT__

#include <MLV/MLV_all.h>
#include "const.h"

/* Structure représentant les différentes entités du jeu */

typedef struct position
{
    int x;
    int y;
} Position;

typedef struct sprite
{
    MLV_Image **frames;
    int nb_frames;
    int current_frame;
    int status;
} Sprite;

typedef struct player
{
    Position *position;
    int health;
    int speed;
    int delay_shoot;
    char *name;
    int shield;
    Sprite *sprite_walk;
    Sprite *sprite_attack;
    Sprite *sprite_dead;
    Sprite *sprite_run;
    Sprite *sprite_idle;
    int height;
    int width;
} Player;

typedef struct bullet_player
{
    Position *position;
    int height;
    int width;
    int size;
    int speed;
    int damage;
    int visible;
} Bullet_player;

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

typedef struct scoreboard
{
    char *name;
    unsigned long int score;
    char *date;
    char *time;
} Scoreboard;

typedef struct party
{
    int verbose_flag;
    int hitbox_flag;
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
    int size_file_scoreboard;
    Scoreboard *scoreboard[10];
    MLV_Image *image_heart_full;
    MLV_Image *image_heart_empty;
    MLV_Image *image_bullet_player;
    MLV_Image *image_enemy;
    MLV_Image *image_bullet_enemy;
    
    MLV_Image *image_shield_bonus;
    MLV_Image *image_speed_bonus;
    MLV_Image *image_health_bonus;
    MLV_Image *image_bomb_bonus;
    MLV_Image *image_slow_penalty;
    MLV_Image *image_reverse_penalty;
    MLV_Image *image_damage_penalty;
    MLV_Image *image_shield;
} Party;

#endif