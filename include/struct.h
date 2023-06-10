#ifndef __STRUCT__
#define __STRUCT__

#include <MLV/MLV_all.h>
#include "const.h"

/**
 * @struct Position
 * @brief Position of an object
*/
typedef struct position
{
    int x;
    int y;
} Position;

/**
 * @struct Sprite
 * @brief Sprite of an object
 */
typedef struct sprite
{
    MLV_Image **frames;
    int nb_frames;
    int current_frame;
    int status;
} Sprite;

/**
 * @struct Player
 * @brief Player of the game
 */
typedef struct player
{
    Position *position;
    int health;
    int speed;
    int delay_shoot;
    char *name;
    int shield;
    int is_reversed;
    Sprite *sprite_walk;
    Sprite *sprite_attack;
    Sprite *sprite_run;
    Sprite *sprite_idle;
    int height;
    int width;
} Player;

/**
 * @struct Bullet_player
 * @brief Bullet of the player
 */
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

/**
 * @struct Enemy
 * @brief Enemy of the game
 */
typedef struct enemy
{
    Position *position;
    int original_y;
    int current_frame;
    int height;
    int width;
    int health;
    int speed;
    int status;
    int visible;
} Enemy;

/**
 * @struct Bullet_enemy
 * @brief Bullet of the enemy
 */
typedef struct bullet_enemy
{
    Position *position;
    int width;
    int height;
    int speed;
    int damage;
    int visible;
} Bullet_enemy;

/**
 * @struct Background
 * @brief Background of the game
 */
typedef struct background
{
    Position *position;
    MLV_Image *image;
} Background;

/**
 * @struct Foreground
 * @brief Foreground of the game
 */
typedef struct foreground
{
    Position *position;
    MLV_Image *image;
} Foreground;

/**
 * @struct Scenery
 * @brief Scenery of the game
 */
typedef struct scenery
{
    Background *background;
    Foreground *foreground;
    int speed;
    int scroll;
} Scenery;

/**
 * @struct Menu
 * @brief Menu of the game
 */
typedef struct menu
{
    Background *background;
    MLV_Font *font_text;
    MLV_Font *font_title;
    MLV_Font *font_text_credits;
    MLV_Image *img_sound_on;
    MLV_Image *img_sound_off;
} Menu;

typedef int Pressed_key[5];

/**
 * @enum Bonus_kind
 * @brief Kind of bonus
 */
typedef enum bonus_kind
{
    SHIELD,
    SPEED,
    HEALTH,
    BOMB,
    ATTACK
} Bonus_kind;

/**
 * @enum Penalty_kind
 * @brief Kind of penalty
 */
typedef enum penalty_kind
{
    SLOW,
    REVERSE,
    BOSS
} Penalty_kind;

/**
 * @struct Bonus
 * @brief Bonus of the game
 */
typedef struct bonus
{
    Position *position;
    Bonus_kind kind;
    int size;
    int speed;
    int visible;
} Bonus;

/**
 * @struct Penalty
 * @brief Penalty of the game
 */
typedef struct penalty
{
    Position *position;
    Penalty_kind kind;
    int size;
    int speed;
    int visible;
} Penalty;

/**
 * @struct Scoreboard
 * @brief Scoreboard of the game
 */
typedef struct scoreboard
{
    char *name;
    unsigned long int score;
    char *date;
    char *time;
} Scoreboard;

/**
 * @struct Party
 * @brief Party of the game
 */
typedef struct party
{
    int verbose_flag;
    int hitbox_flag;
    int sound;
    int status;
    float enemies_density;
    unsigned long int score;
    MLV_Font *text_game;
    Player *player;
    Enemy *enemies[MAX_ENEMY];
    Sprite *sprite_walk_enemy;
    Sprite *sprite_attack_enemy;
    Bullet_player *bullets_player[MAX_BULLET_PLAYER];
    Bullet_enemy *bullets_enemy[MAX_BULLET_ENEMY];
    Penalty *penalty[MAX_PENALTY];
    Bonus *bonus[MAX_BONUS];
    Scenery *scenery1;
    Scenery *scenery2;
    Menu *menu;
    Pressed_key pk;
    Scoreboard *scoreboard[MAX_BEST_SCORE + 1];
    MLV_Image *image_heart_full;
    MLV_Image *image_heart_empty;
    MLV_Image *image_bullet_player;
    MLV_Image *image_bullet_enemy;
    MLV_Image *image_shield_bonus;
    MLV_Image *image_shield_effect;
    MLV_Image *image_speed_bonus;
    MLV_Sound *sound_speed_bonus;
    MLV_Image *image_health_bonus;
    MLV_Image *image_bomb_bonus;
    MLV_Sound *sound_bomb_bonus;
    MLV_Image *image_attack_bonus;
    MLV_Image *image_slow_penalty;
    MLV_Image *image_reverse_penalty;
    MLV_Sound *sound_reverse_penalty;
    MLV_Image *image_boss_penalty;
    MLV_Sound *sound_boss_penalty;
} Party;

#endif