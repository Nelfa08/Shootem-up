#include <MLV/MLV_all.h>

#include "../include/const.h"
#include "../include/struct.h"

#include "../include/window.h"

/**
 * @brief efface le contenu de la window
 *
 * @return int
 */
int clear_window()
{
    MLV_clear_window(MLV_COLOR_BLACK);
    return EXIT_SUCCESS;
}

int init_window_menu()
{
    MLV_create_window(NAME_FRAME_MENU, NULL, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    clear_window();
    draw_loading_screen();
    MLV_actualise_window();
    return EXIT_SUCCESS;
}

int draw_loading_screen()
{
    // @todo: dessiner un écran de chargement
    MLV_draw_text(WIDTH_FRAME_MENU / 2 - 100, HEIGHT_FRAME_MENU / 2 - 50, "Loading...", MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
}

int draw_window_menu(Party *party, int border_sound)
{
    MLV_Image *img = party->menu->background->image;
    MLV_Image *img_sound_on = MLV_load_image(PATH_IMG_SOUND_ON);
    MLV_Image *img_sound_off = MLV_load_image(PATH_IMG_SOUND_OFF);
    MLV_Font *font_title = MLV_load_font(PATH_FONT_MENU, 76);
    MLV_Font *font = MLV_load_font(PATH_FONT_MENU, 50);
    char *name_game = "DofusRuner";
    char *button_play = "PLAY";
    char *button_credits = "CREDITS";
    char *button_quit = "QUIT";
    int width_name_game, height_name_game;
    int width_button_play, height_button_play;
    int width_button_credits, height_button_credits;
    int width_button_quit, height_button_quit;

    /*dessin du background*/
    MLV_resize_image_with_proportions(img, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    MLV_draw_image(img, 0, 0);

    /*dessin du nom du jeu*/
    MLV_get_size_of_text_with_font(name_game, &width_name_game, &height_name_game, font_title);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_name_game / 2), HEIGHT_FRAME_GAME * 2 / 10 - height_name_game / 2, name_game, font_title, MLV_rgba(13, 153, 68, 0));

    /*dessin du bouton jouer*/
    MLV_get_size_of_text_with_font(button_play, &width_button_play, &height_button_play, font);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_button_play / 2), (HEIGHT_FRAME_GAME * 5 / 10 - height_button_play / 2), button_play, font, MLV_rgba(13, 153, 68, 0));

    /*dessin du bouton crédits*/
    MLV_get_size_of_text_with_font(button_credits, &width_button_credits, &height_button_credits, font);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_button_credits / 2), (HEIGHT_FRAME_GAME * 6 / 10 - height_button_credits / 2), button_credits, font, MLV_rgba(13, 153, 68, 0));

    /*dessin du bouton quitter*/
    MLV_get_size_of_text_with_font(button_quit, &width_button_quit, &height_button_quit, font);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_button_quit / 2), (HEIGHT_FRAME_GAME * 7 / 10 - height_button_quit / 2), button_quit, font, MLV_rgba(13, 153, 68, 0));

    if (party->sound == 1)
    {
        /*dessin du bouton son_on*/
        MLV_resize_image_with_proportions(img_sound_on, 50, 50);
        MLV_draw_image(img_sound_on, WIDTH_FRAME_MENU - (SIZE_ICON_MUSIC + border_sound), border_sound);
    }
    else
    {
        /*dessin du bouton son_off*/
        MLV_resize_image_with_proportions(img_sound_off, 50, 50);
        MLV_draw_image(img_sound_off, WIDTH_FRAME_MENU - (SIZE_ICON_MUSIC + border_sound), border_sound);
    }

    /*On rafraichit la fenetre*/
    MLV_actualise_window();

    return EXIT_SUCCESS;
}

int draw_window_credits()
{
    MLV_Image *img = MLV_load_image(PATH_IMG_BG_MENU);
    MLV_Font *font_title = MLV_load_font(PATH_FONT_MENU, 76);
    MLV_Font *font_back = MLV_load_font(PATH_FONT_MENU, 30);
    MLV_Font *font_text = MLV_load_font(PATH_FONT_MENU, 20);
    char *title = "CREDITS";
    char *back = "BACK";
    int width_button_back, height_button_back;
    int width_text_title, height_text_title;
    int width_text_credits, height_text_credits;
    int taille_interlinge = 10;
    char *message_credits = "Developped by :\n    RODDIER Corentin\n    DJEBLOUN Yacine\n\n Music by :\n    LEANO Tristan\n\n Design by :\n    AGRA Ralph";

    MLV_resize_image_with_proportions(img, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    MLV_draw_image(img, 0, 0);

    MLV_get_size_of_text_with_font(title, &width_text_title, &height_text_title, font_title);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_text_title / 2), (HEIGHT_FRAME_GAME * 2 / 10 - height_text_title / 2), title, font_title, MLV_rgba(13, 153, 68, 0));

    MLV_get_size_of_text_with_font(title, &width_button_back, &height_button_back, font_back);
    MLV_draw_text_with_font(10, 0, back, font_back, MLV_COLOR_RED1);

    MLV_get_size_of_adapted_text_box_with_font(message_credits, font_text, taille_interlinge, &width_text_credits, &height_text_credits);

    MLV_draw_adapted_text_box_with_font((WIDTH_FRAME_MENU / 2) - (width_text_credits / 2), (HEIGHT_FRAME_GAME * 3 / 10 - height_button_back / 2), message_credits, font_text, taille_interlinge, MLV_ALPHA_TRANSPARENT, MLV_COLOR_GREEN, MLV_ALPHA_TRANSPARENT, MLV_TEXT_LEFT);

    MLV_actualise_window();
    MLV_free_image(img);
    MLV_free_font(font_title);
    MLV_free_font(font_back);
    return EXIT_SUCCESS;
}

/**
 * @brief initialisation de la window
 *
 * @return int
 */
int init_window_game()
{
    MLV_change_window_size(WIDTH_FRAME_GAME, HEIGHT_FRAME_GAME);
    MLV_change_window_caption(NAME_FRAME_GAME, NULL);
    clear_window();
    return EXIT_SUCCESS;
}

/**
 * @brief redessine la window
 *
 * @param player
 * @return int
 */
int draw_frame_game(Party *party)
{
    draw_background(party->scenery1->background);
    draw_background(party->scenery2->background);

    draw_health(party);
    draw_player(party);
    draw_bullet_player(party);
    draw_enemies(party);
    draw_bullet_enemy(party);

    draw_foreground(party->scenery1->foreground);
    draw_foreground(party->scenery2->foreground);
    draw_score(party);
    MLV_actualise_window();
    return EXIT_SUCCESS;
}

int move_scenery(Scenery *scenery1, Scenery *scenery2)
{
    scenery1->background->position->x -= SPEED_BG_GAME;
    scenery1->foreground->position->x -= SPEED_BG_GAME;
    scenery2->background->position->x -= SPEED_BG_GAME;
    scenery2->foreground->position->x -= SPEED_BG_GAME;
    if (scenery1->background->position->x <= -WIDTH_FRAME_GAME)
    {
        scenery1->background->position->x = WIDTH_FRAME_GAME;
    }
    if (scenery1->foreground->position->x <= -WIDTH_FRAME_GAME)
    {
        scenery1->foreground->position->x = WIDTH_FRAME_GAME;
    }
    if (scenery2->background->position->x <= -WIDTH_FRAME_GAME)
    {
        scenery2->background->position->x = WIDTH_FRAME_GAME;
    }
    if (scenery2->foreground->position->x <= -WIDTH_FRAME_GAME)
    {
        scenery2->foreground->position->x = WIDTH_FRAME_GAME;
    }
    return EXIT_SUCCESS;
}

int draw_background(Background *background)
{
    MLV_Image *bg1 = background->image;
    MLV_resize_image_with_proportions(bg1, WIDTH_FRAME_GAME, HEIGHT_FRAME_GAME);
    MLV_draw_image(bg1, background->position->x, background->position->y);
    return EXIT_SUCCESS;
}

int draw_foreground(Foreground *foreground)
{
    MLV_Image *fg1 = foreground->image;
    MLV_resize_image_with_proportions(fg1, WIDTH_FRAME_GAME, HEIGHT_FRAME_GAME);
    MLV_draw_image(fg1, foreground->position->x, foreground->position->y);
    return EXIT_SUCCESS;
}

int draw_health(Party *party)
{
    for (int i = 0; i < HEALTH_PLAYER; i++)
    {
        if (party->player->health > i)
        {
            MLV_resize_image_with_proportions(party->image_heart_full, SIZE_HEART, SIZE_HEART);
            MLV_draw_image(party->image_heart_full, SIZE_HEART + (i * SIZE_HEART), SIZE_HEART);
        }
        else
        {
            MLV_resize_image_with_proportions(party->image_heart_empty, SIZE_HEART, SIZE_HEART);
            MLV_draw_image(party->image_heart_empty, SIZE_HEART + (i * SIZE_HEART), SIZE_HEART);
        }
    }
    return EXIT_SUCCESS;
}

int draw_player(Party *party)
{
    MLV_resize_image_with_proportions(party->image_player, party->player->size, party->player->size);
    MLV_draw_image(party->image_player, party->player->position->x, party->player->position->y);
    /* dessine les hitbox */
    MLV_draw_rectangle(party->player->position->x, party->player->position->y, party->player->size, party->player->size, MLV_COLOR_RED);
    return 0;
}

int draw_enemies(Party *party)
{
    int i;
    for (i = 0; i < MAX_ENEMY; i++)
    {
        if (party->enemies[i]->visible == 1)
        {
            MLV_resize_image_with_proportions(party->image_enemy, party->enemies[i]->size, party->enemies[i]->size);
            MLV_draw_image(party->image_enemy, party->enemies[i]->position->x, party->enemies[i]->position->y);
            /* dessine les hitbox */
            MLV_draw_rectangle(party->enemies[i]->position->x, party->enemies[i]->position->y, party->enemies[i]->size, party->enemies[i]->size, MLV_COLOR_RED);
        }
    }
    return 0;
}

int draw_score(Party *party)
{
    char score[1000];
    sprintf(score, "Score: %ld", party->score);
    MLV_draw_text(10, 10, score, MLV_COLOR_RED);
    return 0;
}

int draw_bullet_player(Party *party)
{
    int i;
    for (i = 0; i < MAX_BULLET_PLAYER; i++)
    {
        if (party->bullets_player[i]->visible == 1)
        {
            MLV_resize_image_with_proportions(party->image_bullet_player, party->bullets_player[i]->size, party->bullets_player[i]->size);
            MLV_draw_image(party->image_bullet_player, party->bullets_player[i]->position->x, party->bullets_player[i]->position->y);
            /* dessine les hitbox */

            MLV_draw_rectangle(party->bullets_player[i]->position->x, party->bullets_player[i]->position->y, party->bullets_player[i]->size, party->bullets_player[i]->size, MLV_COLOR_RED);
        }
    }

    return 0;
}

int draw_bullet_enemy(Party *party)
{
    int i;
    for (i = 0; i < MAX_BULLET_ENEMY; i++)
    {
        if (party->bullets_enemy[i]->visible == 1)
        {
            MLV_resize_image_with_proportions(party->image_bullet_enemy, party->bullets_enemy[i]->width, party->bullets_enemy[i]->height);
            MLV_draw_image(party->image_bullet_enemy, party->bullets_enemy[i]->position->x, party->bullets_enemy[i]->position->y);
            /* dessine les hitbox */

            MLV_draw_rectangle(party->bullets_enemy[i]->position->x, party->bullets_enemy[i]->position->y, party->bullets_enemy[i]->width, party->bullets_enemy[i]->height, MLV_COLOR_RED);
        }
    }

    return 0;
}

int draw_window_end(Party *party)
{
    MLV_Image *img = party->menu->background->image;
    MLV_change_window_size(WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    clear_window();

    MLV_resize_image_with_proportions(img, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    MLV_draw_image(img, 0, 0);

    MLV_actualise_window();
    return EXIT_SUCCESS;
}

int draw_input_name(Party *party)
{
    char *player_name;
    MLV_Font *font = MLV_load_font(PATH_FONT_MENU, 30);

    MLV_wait_input_box_with_font(WIDTH_FRAME_GAME / 4, HEIGHT_FRAME_GAME / 4, WIDTH_FRAME_GAME / 4 + 100, HEIGHT_FRAME_GAME / 4 + 100, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_COLOR_BLACK, "Player name: ", &player_name, font);

    MLV_actualise_window();

    party->player->name = player_name;

    MLV_free_font(font);
    return EXIT_SUCCESS;
}

/**
 * @brief libère en mémoire la window
 *
 * @return int
 */
int free_window()
{
    MLV_free_window();
    return EXIT_SUCCESS;
}