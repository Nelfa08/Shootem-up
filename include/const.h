/* Fichier de définition de l'ensemble des constantes.*/

#ifndef __CONST__
#define __CONST__

#define BILLION 1000000000

/* FRAME MENU */
#define HEIGHT_FRAME_MENU 750
#define WIDTH_FRAME_MENU 750
#define NAME_FRAME_MENU "DofusRuner - Menu"
#define PATH_IMG_BG_MENU "data/img/bg_menu.png"
#define PATH_IMG_SOUND_ON "data/img/sound_on.png"
#define PATH_IMG_SOUND_OFF "data/img/sound_off.png"
#define PATH_FONT_MENU "data/font/Talk_Comic.ttf"
#define PATH_MUSIC_MENU "data/music/music.wav"
#define VOL_MUSIC_MENU 0.1
#define SIZE_ICON_MUSIC 50

/* FRAME CREDITS */


/* FRAME GAME */
#define HEIGHT_FRAME_GAME 800
#define WIDTH_FRAME_GAME 1500
#define TOP_BORDER 260
#define BOTTOM_BORDER 630
#define NAME_FRAME_GAME "DofusRuner - Game"

/* SCENERY */
#define PATH_IMG_BG_GAME "data/img/bg_game.png"
#define PATH_IMG_FG_GAME "data/img/fg_game.png"
#define SPEED_BG_GAME 1

/* PLAYER */
#define SIZE_PLAYER 100
#define PATH_PLAYER "data/img/player.png"
#define PATH_IMG_HEART_FULL "data/img/heart_full.png"
#define PATH_IMG_HEART_EMPTY "data/img/heart.png"
#define SIZE_HEART 20
#define SPEED_PLAYER 10
#define HEALTH_PLAYER 3
#define SPAWN_PLAYER_X 0
#define SPAWN_PLAYER_Y 260
#define DELAY_SHOOT_PLAYER 7

/* BULLET PLAYER */
#define PATH_IMG_BULLET_PLAYER "data/img/shuriken.png"
#define SIZE_BULLET_PLAYER 30
#define SPEED_BULLET_PLAYER 30
#define DAMAGE_BULLET_PLAYER 1
#define MAX_BULLET_PLAYER 100

/* ENEMY */
#define SIZE_ENEMY 100
#define PATH_ENEMY "data/img/dragon.png"
#define SPEED_ENEMY 3
#define HEALTH_ENEMY 1
#define MAX_ENEMY 100

/* BULLET ENEMY */
#define PATH_IMG_BULLET_ENEMY "data/img/bullet_enemy.png"
#define WIDTH_BULLET_ENEMY 40
#define HEIGHT_BULLET_ENEMY 20
#define SPEED_BULLET_ENEMY 5
#define DAMAGE_BULLET_ENEMY 1
#define MAX_BULLET_ENEMY 100

/* BONUS */
#define SIZE_BONUS 50
#define MAX_BONUS 100
#define SPEED_BONUS 5

/* PENALTIES */
#define SIZE_PENALTY 50
#define MAX_PENALTY 100
#define SPEED_PENALTY 5

#endif