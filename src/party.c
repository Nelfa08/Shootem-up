#include <MLV/MLV_all.h>


#include "../include/struct.h"
#include "../include/const.h"

#include "../include/party.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/keyboard_listener.h"
#include "../include/bullet_player.h"
#include "../include/bullet_enemy.h"

/*Ici il faut mettre la création de la party
* Initialisation d'une structure party avec l'état (menu, en cours, fini), le niveau choisi, etc
*/

/* Il faut aussi initialiser le table d'ennemies et de missile (soit le mettre ici soit dans enemy.c et buller_enemy(fichier à créer))*/


Party *init_party()
{
    Party *party = malloc(sizeof(Party));
    party->state = 0;
    party->sound = 0;
    party->score = 0;

    party->player = create_player();

    init_tab_enemy(party);
    init_bullets_player(party);
    init_bullets_enemy(party);

    /* A mettre dans des sous fonctions */
    party->scenery1 = malloc(sizeof(Scenery));
    party->scenery1->background = malloc(sizeof(Background));
    party->scenery1->background->position = malloc(sizeof(Position));
    party->scenery1->background->position->x = 0;
    party->scenery1->background->position->y = 0;
    party->scenery1->background->image = MLV_load_image(PATH_IMG_BG_GAME);
    party->scenery1->foreground = malloc(sizeof(Foreground));
    party->scenery1->foreground->position = malloc(sizeof(Position));
    party->scenery1->foreground->position->x = 0;
    party->scenery1->foreground->position->y = 0;
    party->scenery1->foreground->image = MLV_load_image(PATH_IMG_FG_GAME);
    party->scenery1->scroll = 1;
    party->scenery1->speed = SPEED_BG_GAME;

    party->scenery2 = malloc(sizeof(Scenery));
    party->scenery2->background = malloc(sizeof(Background));
    party->scenery2->background->position = malloc(sizeof(Position));
    party->scenery2->background->position->x = WIDTH_FRAME_GAME;
    party->scenery2->background->position->y = 0;
    party->scenery2->background->image = MLV_load_image(PATH_IMG_BG_GAME);
    party->scenery2->foreground = malloc(sizeof(Foreground));
    party->scenery2->foreground->position = malloc(sizeof(Position));
    party->scenery2->foreground->position->x = WIDTH_FRAME_GAME;
    party->scenery2->foreground->position->y = 0;
    party->scenery2->foreground->image = MLV_load_image(PATH_IMG_FG_GAME);

    party->menu = malloc(sizeof(Menu));
    party->menu->background = malloc(sizeof(Background));
    party->menu->background->position = malloc(sizeof(Position));
    party->menu->background->position->x = 0;
    party->menu->background->position->y = 0;
    party->menu->background->image = MLV_load_image(PATH_IMG_BG_MENU);
    party->menu->font_text = MLV_load_font(PATH_FONT_MENU, 50);
    party->menu->font_title = MLV_load_font(PATH_FONT_MENU, 76);
    party->menu->img_sound_on = MLV_load_image(PATH_IMG_SOUND_ON);
    party->menu->img_sound_off = MLV_load_image(PATH_IMG_SOUND_OFF);

    party->image_player = MLV_load_image(PATH_PLAYER);
    party->image_bullet_player = MLV_load_image(PATH_IMG_BULLET_PLAYER);
    party->image_enemy = MLV_load_image(PATH_ENEMY);
    party->image_bullet_enemy = MLV_load_image(PATH_IMG_BULLET_ENEMY);
    party->image_heart_empty = MLV_load_image(PATH_IMG_HEART_EMPTY);
    party->image_heart_full = MLV_load_image(PATH_IMG_HEART_FULL);

    return party;
}

int free_party(Party *party)
{
    free_player(party->player);
    free(party);
    return EXIT_SUCCESS;
}