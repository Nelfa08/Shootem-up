/**
 * @file window.c
 * @author Corentin RODDIER and Yacine DJEBLOUN
 * @brief File containing all the functions about the window
 * @version 1.0
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MLV/MLV_all.h>
#include <string.h>

#include "../include/const.h"
#include "../include/struct.h"

#include "../include/window.h"

/**
 * @brief clear the window
 * 
 * @return int 
 */
int clear_window()
{
    MLV_clear_window(MLV_COLOR_BLACK);
    return EXIT_SUCCESS;
}

/**
 * @brief init the window of the menu
 * 
 * @return int 
 */
int init_window_menu()
{
    MLV_create_window(NAME_FRAME_MENU, NULL, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    clear_window();
    draw_loading_screen();

    MLV_actualise_window();
    return EXIT_SUCCESS;
}

/**
 * @brief draw the loading screen
 * 
 * @return int 
 */
int draw_loading_screen()
{
    MLV_draw_text(WIDTH_FRAME_MENU / 2 - 30, HEIGHT_FRAME_MENU / 2 - 20, "Loading...", MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
}

/**
 * @brief draw the window of the menu
 * 
 * @param party 
 * @return int 
 */
int draw_window_menu(Party *party)
{
    char *name_game = strdup("DofusRunner");
    char *button_play = strdup("PLAY");
    char *button_credits = strdup("CREDITS");
    char *button_quit = strdup("QUIT");
    int width_name_game, height_name_game;
    int width_button_play, height_button_play;
    int width_button_credits, height_button_credits;
    int width_button_quit, height_button_quit;

    /*dessin du background*/
    MLV_resize_image_with_proportions(party->menu->background->image, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    MLV_draw_image(party->menu->background->image, party->menu->background->position->x, party->menu->background->position->y);

    /*dessin du nom du jeu*/
    MLV_get_size_of_text_with_font(name_game, &width_name_game, &height_name_game, party->menu->font_title);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_name_game / 2), HEIGHT_FRAME_GAME * 2 / 10 - height_name_game / 2, name_game, party->menu->font_title, MLV_rgba(209, 94, 50, 0));

    /*dessin du bouton jouer*/
    MLV_get_size_of_text_with_font(button_play, &width_button_play, &height_button_play, party->menu->font_text);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_button_play / 2), (HEIGHT_FRAME_GAME * 5 / 10 - height_button_play / 2), button_play, party->menu->font_text, MLV_rgba(211, 117, 81, 0));

    /*dessin du bouton crédits*/
    MLV_get_size_of_text_with_font(button_credits, &width_button_credits, &height_button_credits, party->menu->font_text);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_button_credits / 2), (HEIGHT_FRAME_GAME * 6 / 10 - height_button_credits / 2), button_credits, party->menu->font_text, MLV_rgba(211, 117, 81, 0));

    /*dessin du bouton quitter*/
    MLV_get_size_of_text_with_font(button_quit, &width_button_quit, &height_button_quit, party->menu->font_text);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_button_quit / 2), (HEIGHT_FRAME_GAME * 7 / 10 - height_button_quit / 2), button_quit, party->menu->font_text, MLV_rgba(211, 117, 81, 0));

    if (party->sound == 1)
    {
        /*dessin du bouton son_on*/
        MLV_resize_image_with_proportions(party->menu->img_sound_on, 50, 50);
        MLV_draw_image(party->menu->img_sound_on, WIDTH_FRAME_MENU - (SIZE_ICON_MUSIC + 10), 10);
    }
    else
    {
        /*dessin du bouton son_off*/
        MLV_resize_image_with_proportions( party->menu->img_sound_off, 50, 50);
        MLV_draw_image(party->menu->img_sound_off, WIDTH_FRAME_MENU - (SIZE_ICON_MUSIC + 10), 10);
    }

    MLV_draw_image(party->player->sprite_idle->frames[party->player->sprite_idle->current_frame], 0, 0);

    party->player->sprite_idle->current_frame++;

    if (party->player->sprite_idle->current_frame >= party->player->sprite_idle->nb_frames)
    {
        party->player->sprite_idle->current_frame = 0;
    }

    MLV_wait_milliseconds(500 / party->player->sprite_idle->nb_frames);

    /*On rafraichit la fenetre*/
    MLV_actualise_window();

    free(name_game);
    free(button_play);
    free(button_credits);
    free(button_quit);
    
    return EXIT_SUCCESS;
}

/**
 * @brief draw the window of the credits
 * 
 * @return int 
 */
int draw_window_credits(Party *party)
{
    char *title = "CREDITS";
    char *back = "BACK";
    int width_button_back, height_button_back;
    int width_text_title, height_text_title;
    int width_text_credits, height_text_credits;
    int taille_interlinge = 10;
    char *message_credits = "DEVELOPPED BY :\n    RODDIER CORENTIN\n    DJEBLOUN YACINE\n\n MUSIC BY :\n    LEANO TRISTAN\n\n DESIGN BY :\n    AGRA RALPH";

    MLV_resize_image_with_proportions(party->menu->background->image, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    MLV_draw_image(party->menu->background->image, 0, 0);

    MLV_get_size_of_text_with_font(title, &width_text_title, &height_text_title, party->menu->font_title);
    MLV_draw_text_with_font((WIDTH_FRAME_MENU / 2) - (width_text_title / 2), (HEIGHT_FRAME_GAME * 2 / 10 - height_text_title / 2), title, party->menu->font_title, MLV_rgba(209, 94, 50, 0));

    MLV_get_size_of_text_with_font(title, &width_button_back, &height_button_back, party->menu->font_text_credits);
    MLV_draw_text_with_font(10, 0, back, party->menu->font_text_credits, MLV_rgba(209, 94, 50, 0));

    MLV_get_size_of_adapted_text_box_with_font(message_credits, party->menu->font_text_credits, taille_interlinge, &width_text_credits, &height_text_credits);

    MLV_draw_adapted_text_box_with_font((WIDTH_FRAME_MENU / 2) - (width_text_credits / 2), (HEIGHT_FRAME_GAME * 3 / 10 - height_button_back / 2), message_credits, party->menu->font_text_credits, taille_interlinge, MLV_COLOR_WHITE_SMOKE, MLV_rgba(211, 117, 81, 0), MLV_COLOR_WHITE_SMOKE, MLV_TEXT_LEFT);

    MLV_actualise_window();
    // MLV_free_font(font_title);
    // MLV_free_font(font_back);
    // MLV_free_font(font_text);
    return EXIT_SUCCESS;
}

/**
 * @brief init the window of the game
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
 * @brief draw the window of the game and the elements
 * 
 * @param party 
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
    draw_bonus(party);
    draw_penalties(party);

    if (party->player->shield != 0)
    {
        draw_shield(party);
    }

    draw_foreground(party->scenery1->foreground);
    draw_foreground(party->scenery2->foreground);
    draw_score(party);
    MLV_actualise_window();
    return EXIT_SUCCESS;
}

/**
 * @brief move the scenery
 * 
 * @param scenery1 
 * @param scenery2 
 * @return int 
 */
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

/**
 * @brief draw the background
 * 
 * @param background 
 * @return int 
 */
int draw_background(Background *background)
{
    MLV_Image *bg1 = background->image;
    MLV_resize_image_with_proportions(bg1, WIDTH_FRAME_GAME, HEIGHT_FRAME_GAME);
    MLV_draw_image(bg1, background->position->x, background->position->y);
    return EXIT_SUCCESS;
}

/**
 * @brief draw the foreground
 * 
 * @param foreground 
 * @return int 
 */
int draw_foreground(Foreground *foreground)
{
    MLV_Image *fg1 = foreground->image;
    MLV_resize_image_with_proportions(fg1, WIDTH_FRAME_GAME, HEIGHT_FRAME_GAME);
    MLV_draw_image(fg1, foreground->position->x, foreground->position->y);
    return EXIT_SUCCESS;
}

/**
 * @brief draw the health of the player
 * 
 * @param party 
 * @return int 
 */
int draw_health(Party *party)
{
    for (int i = 0; i < HEALTH_PLAYER; i++)
    {
        if (party->player->health > i)
        {
            MLV_resize_image_with_proportions(party->image_heart_full, SIZE_HEART, SIZE_HEART);
            MLV_draw_image(party->image_heart_full, SIZE_HEART + (i * SIZE_HEART), 50);
        }
        else
        {
            MLV_resize_image_with_proportions(party->image_heart_empty, SIZE_HEART, SIZE_HEART);
            MLV_draw_image(party->image_heart_empty, SIZE_HEART + (i * SIZE_HEART), 50);
        }
    }
    return EXIT_SUCCESS;
}

/**
 * @brief draw the player
 * 
 * @param party 
 * @return int 
 */
int draw_player(Party *party)
{
    if (party->player->sprite_attack->status == 1)
    {
        MLV_draw_image(party->player->sprite_attack->frames[party->player->sprite_attack->current_frame], party->player->position->x, party->player->position->y);
        party->player->sprite_attack->current_frame++;
        if (party->player->sprite_attack->current_frame >= party->player->sprite_attack->nb_frames)
        {
            party->player->sprite_attack->current_frame = 0;
            party->player->sprite_attack->status = 0;
        }

        /* dessine les hitbox */
        if (party->hitbox_flag == 1)
        {
            MLV_draw_rectangle(party->player->position->x, party->player->position->y, party->player->width, party->player->height, MLV_COLOR_RED);
        }
    }
    else if (party->player->sprite_run->status == 1)
    {
        MLV_draw_image(party->player->sprite_run->frames[party->player->sprite_run->current_frame], party->player->position->x, party->player->position->y);
        if (party->score % 2 == 0)
        {
            party->player->sprite_run->current_frame++;
        }
        if (party->player->sprite_run->current_frame >= party->player->sprite_run->nb_frames)
        {
            party->player->sprite_run->current_frame = 0;
        }
    }
    else
    {
        MLV_draw_image(party->player->sprite_walk->frames[party->player->sprite_walk->current_frame], party->player->position->x, party->player->position->y);
        if (party->score % 2 == 0)
        {
            party->player->sprite_walk->current_frame++;
        }
        if (party->player->sprite_walk->current_frame >= party->player->sprite_walk->nb_frames)
        {
            party->player->sprite_walk->current_frame = 0;
        }

        /* dessine les hitbox */
        if (party->hitbox_flag == 1)
        {
            MLV_draw_rectangle(party->player->position->x, party->player->position->y, party->player->width, party->player->height, MLV_COLOR_RED);
        }
    }
    MLV_wait_milliseconds(100 / party->player->sprite_walk->nb_frames);
    return 0;
}

/**
 * @brief draw the enemies
 * 
 * @param party 
 * @return int 
 */
int draw_enemies(Party *party)
{
    int i;
    for (i = 0; i < MAX_ENEMY; i++)
    {
        if (party->enemies[i]->visible == 1)
        {
            if (party->enemies[i]->status == 1)
            {
                MLV_draw_image(party->sprite_attack_enemy->frames[party->enemies[i]->current_frame], party->enemies[i]->position->x, party->enemies[i]->position->y);
                party->enemies[i]->current_frame++;
                if (party->enemies[i]->current_frame >= party->sprite_attack_enemy->nb_frames)
                {
                    party->enemies[i]->current_frame = 0;
                    party->enemies[i]->status = 0;
                }

                /* dessine les hitbox */
                if (party->hitbox_flag == 1)
                {
                    MLV_draw_rectangle(party->enemies[i]->position->x, party->enemies[i]->position->y, party->enemies[i]->width, party->enemies[i]->height, MLV_COLOR_RED);
                }
            }
            else
            {
                MLV_draw_image(party->sprite_walk_enemy->frames[party->enemies[i]->current_frame], party->enemies[i]->position->x, party->enemies[i]->position->y);
                if (party->score % 2 == 0)
                {
                    party->enemies[i]->current_frame++;
                }
                if (party->enemies[i]->current_frame >= party->sprite_walk_enemy->nb_frames)
                {
                    party->enemies[i]->current_frame = 0;
                }

                /* dessine les hitbox */
                if (party->hitbox_flag == 1)
                {
                    MLV_draw_rectangle(party->enemies[i]->position->x, party->enemies[i]->position->y, party->enemies[i]->width, party->enemies[i]->height, MLV_COLOR_RED);
                }
            }
        }
    }
    return 0;
}

/**
 * @brief draw the score
 * 
 * @param party 
 * @return int 
 */
int draw_score(Party *party)
{
    char score[1000];
    sprintf(score, "Score: %ld", party->score);
    MLV_draw_text_with_font(30, 10, score, party->text_game, MLV_COLOR_RED);
    return EXIT_SUCCESS;
}

/**
 * @brief draw thr bullets of the player
 * 
 * @param party 
 * @return int 
 */
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
            if (party->hitbox_flag == 1)
            {
                MLV_draw_rectangle(party->bullets_player[i]->position->x, party->bullets_player[i]->position->y, party->bullets_player[i]->size, party->bullets_player[i]->size, MLV_COLOR_RED);
            }
        }
    }

    return 0;
}

/**
 * @brief draw the bullets of the enemies
 * 
 * @param party 
 * @return int 
 */
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
            if (party->hitbox_flag == 1)
            {
                MLV_draw_rectangle(party->bullets_enemy[i]->position->x, party->bullets_enemy[i]->position->y, party->bullets_enemy[i]->width, party->bullets_enemy[i]->height, MLV_COLOR_RED);
            }
        }
    }

    return 0;
}

/**
 * @brief draw the end of the game
 * 
 * @param party 
 * @return int 
 */
int draw_window_end(Party *party)
{
    // MLV_Image *img = party->menu->background->image;
    MLV_change_window_size(WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    clear_window();

    MLV_resize_image_with_proportions(party->menu->background->image, WIDTH_FRAME_MENU, HEIGHT_FRAME_MENU);
    MLV_draw_image(party->menu->background->image, party->menu->background->position->x, party->menu->background->position->y);
    draw_best_score(party);
    MLV_actualise_window();
    return EXIT_SUCCESS;
}

/**
 * @brief ask the name of the player at the end of the game
 * 
 * @param party 
 * @return int 
 */
int draw_input_name(Party *party)
{
    MLV_Font *font = MLV_load_font(PATH_FONT_MENU, 30);

    MLV_wait_input_box_with_font(WIDTH_FRAME_GAME / 4, HEIGHT_FRAME_GAME / 4, WIDTH_FRAME_GAME / 4 + 100, HEIGHT_FRAME_GAME / 4 + 100, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_COLOR_BLACK, "Player name: ", &party->player->name, font);
    MLV_actualise_window();

    MLV_free_font(font);
    return EXIT_SUCCESS;
}

/**
 * @brief draw bonus according to their kind
 * 
 * @param party 
 * @return int 
 */
int draw_bonus(Party *party)
{
    int i;
    MLV_Image *image_bonus;
    for (i = 0; i < MAX_BONUS; i++)
    {
        if (party->bonus[i]->visible == 1)
        {
            switch (party->bonus[i]->kind)
            {
            case SHIELD:
                image_bonus = party->image_shield_bonus;
                break;
            case SPEED:
                image_bonus = party->image_speed_bonus;
                break;
            case HEALTH:
                image_bonus = party->image_health_bonus;
                break;
            case BOMB:
                image_bonus = party->image_bomb_bonus;
                break;
            case ATTACK:
                image_bonus = party->image_attack_bonus;
                break;
            }
            MLV_resize_image_with_proportions(image_bonus, party->bonus[i]->size, party->bonus[i]->size);
            MLV_draw_image(image_bonus, party->bonus[i]->position->x, party->bonus[i]->position->y);
            /* dessine les hitbox */
            if (party->hitbox_flag == 1)
            {
                MLV_draw_rectangle(party->bonus[i]->position->x, party->bonus[i]->position->y, party->bonus[i]->size, party->bonus[i]->size, MLV_COLOR_RED);
            }
        }
    }
    return 0;
}

/**
 * @brief draw the penalties according to their kind
 * 
 * @param party 
 * @return int 
 */
int draw_penalties(Party *party)
{
    int i;
    MLV_Image *image_penalty;
    for (i = 0; i < MAX_PENALTY; i++)
    {
        if (party->penalty[i]->visible == 1)
        {
            switch (party->penalty[i]->kind)
            {
            case SLOW:
                image_penalty = party->image_slow_penalty;
                break;
            case REVERSE:
                image_penalty = party->image_reverse_penalty;
                break;
            case BOSS:
                image_penalty = party->image_boss_penalty;
                break;
            }
            MLV_resize_image_with_proportions(image_penalty, party->penalty[i]->size, party->penalty[i]->size);
            MLV_draw_image(image_penalty, party->penalty[i]->position->x, party->penalty[i]->position->y);
            /* dessine les hitbox */
            if (party->hitbox_flag == 1)
            {
                MLV_draw_rectangle(party->penalty[i]->position->x, party->penalty[i]->position->y, party->penalty[i]->size, party->penalty[i]->size, MLV_COLOR_RED);
            }
        }
    }
    return 0;
}

/**
 * @brief draw the shield if the player has one
 * 
 * @param party 
 * @return int 
 */
int draw_shield(Party *party)
{
    MLV_resize_image_with_proportions(party->image_shield_effect, party->player->width, party->player->height);
    MLV_draw_image(party->image_shield_effect, party->player->position->x, party->player->position->y);
    /* dessine les hitbox */
    if (party->hitbox_flag == 1)
    {
        MLV_draw_rectangle(party->player->position->x, party->player->position->y, party->player->width, party->player->height, MLV_COLOR_RED);
    }
    return 0;
}

/**
 * @brief draw best score at the end of the game
 * 
 * @param party 
 */
void draw_best_score(Party *party)
{
    MLV_Font *font = MLV_load_font(PATH_FONT_MENU, 15);
    char score[50];
    MLV_draw_filled_rectangle(WIDTH_FRAME_MENU/3 - 30,HEIGHT_FRAME_MENU / 3 - 30,300,745,MLV_COLOR_WHITE);
    for (int i = 0; i < MAX_BEST_SCORE; i++)
    {
        if (party->scoreboard[i]->score != 0)
        {
            sprintf(score, "%ld", party->scoreboard[i]->score);
            MLV_draw_text_with_font(WIDTH_FRAME_MENU / 3, HEIGHT_FRAME_MENU / 3 + 50 * i, party->scoreboard[i]->name, font, MLV_rgba(209, 94, 50, 0));
            MLV_draw_text_with_font(WIDTH_FRAME_MENU / 3 + 200, HEIGHT_FRAME_MENU / 3 + 50 * i, score, font, MLV_rgba(211, 117, 81, 0));
        }
    }
    MLV_free_font(font);
}