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
    return EXIT_SUCCESS;
}

int draw_window_menu()
{
    MLV_Image *img = MLV_load_image(PATH_IMG_MENU);
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

    /*On rafraichit la fenetre*/
    MLV_actualise_window();
    MLV_free_image(img);
    MLV_free_font(font_title);
    MLV_free_font(font);

    return EXIT_SUCCESS;
}

int draw_window_credits()
{
    MLV_Image *img = MLV_load_image(PATH_IMG_MENU);
    MLV_Font *font_title = MLV_load_font(PATH_FONT_MENU, 76);
    MLV_Font *font_back = MLV_load_font(PATH_FONT_MENU, 30);
    char *title = "CREDITS";
    char *back = "BACK";
    int width_button_back, height_button_back;
    int taille_interlinge = 10;

    MLV_resize_image_with_proportions(img, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    MLV_draw_image(img, 0, 0);

    MLV_get_size_of_text_with_font(title, &width_button_back, &height_button_back, font_title);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_button_back / 2), (HEIGHT_FRAME_GAME * 2 / 10 - height_button_back / 2), title, font_title, MLV_rgba(13, 153, 68, 0));

    MLV_get_size_of_text_with_font(title, &width_button_back, &height_button_back, font_back);
    MLV_draw_text_with_font(10, 0, back, font_back, MLV_COLOR_RED1);

    MLV_draw_filled_rectangle(10, 150, 400, 200, MLV_rgba(0, 0, 0, 0));
    MLV_draw_adapted_text_box(10, 150, "Même chose,\nmais le texte\nest justifié à gauche\nde la fenêtre.", taille_interlinge, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, MLV_TEXT_LEFT);

    // http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/beginner_204_texts_and_boxes_8c-example.html

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
int draw_frame_game(Player *player)
{
    MLV_Image *player_img = player->image;
    MLV_Image *bg1 = MLV_load_image(PATH_IMG_GAME);
    // MLV_Image *bg2;
    MLV_resize_image_with_proportions(bg1, WIDTH_FRAME_GAME, HEIGHT_FRAME_GAME);
    MLV_draw_image(bg1, 0, 0);

    MLV_resize_image_with_proportions(player_img, player->size, player->size);
    MLV_draw_image(player_img, player->position->x, player->position->y);
    MLV_actualise_window();
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