/**
 * @file party.c
 * @author Corentin RODDIER and Yacine DJEBLOUN
 * @brief File containing all the functions about the party
 * @version 1.0
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "../include/struct.h"
#include "../include/const.h"

#include "../include/party.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/keyboard_listener.h"
#include "../include/bullet_player.h"
#include "../include/bullet_enemy.h"
#include "../include/penalty.h"
#include "../include/bonus.h"

/**
 * @brief generate a random number between 0 and 1
 *
 * @param mean
 * @return double
 */
double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}

/**
 * @brief Initialize party
 *
 * @param verbose_flag
 * @param hitbox_flag
 * @return Party*
 */
Party *init_party(int verbose_flag, int hitbox_flag)
{
    clock_t start, end;
    MLV_Image *loading_images[NB_IMG_LOADING];
    start = clock();
    if (verbose_flag)
    {
        printf("--------------------------------\n");
        printf("Party initialization started: \n");
    }
    Party *party = malloc(sizeof(Party));
    init_img_loading(loading_images);

    party->verbose_flag = verbose_flag;
    party->hitbox_flag = hitbox_flag;
    party->sound = 1;
    party->status = 0;
    party->enemies_density = ENEMIES_DENSITY;
    party->score = 0;
    party->text_game = MLV_load_font(PATH_FONT_MENU, 20);

    MLV_draw_image(loading_images[0], WIDTH_FRAME_MENU / 2 - 80, HEIGHT_FRAME_MENU - 50);
    MLV_actualise_window();

    party->player = create_player();
    if (verbose_flag)
    {
        printf("\tPlayer created\n");
    }

    init_enemies(party);
    if (verbose_flag)
    {
        printf("\tEnemies created\n");
    }
    init_bullets_player(party);
    if (verbose_flag)
    {
        printf("\tBullets player created\n");
    }
    init_bullets_enemy(party);
    if (verbose_flag)
    {
        printf("\tBullets enemy created\n");
    }

    init_tab_penalty(party);
    if (verbose_flag)
    {
        printf("\tPenalties created\n");
    }
    init_tab_bonus(party);
    if (verbose_flag)
    {
        printf("\tBonuses created\n");
    }

    MLV_draw_image(loading_images[1], WIDTH_FRAME_MENU / 2 - 80, HEIGHT_FRAME_MENU - 50);
    MLV_actualise_window();

    init_scenery(party, loading_images);
    if (verbose_flag)
    {
        printf("\tScenery created\n");
    }

    MLV_draw_image(loading_images[3], WIDTH_FRAME_MENU / 2 - 80, HEIGHT_FRAME_MENU - 50);
    MLV_actualise_window();

    init_menu(party);
    if (verbose_flag)
    {
        printf("\tMenu created\n");
    }

    init_scoreboard(party);
    if (verbose_flag)
    {
        printf("\tScoreboard created\n");
    }

    MLV_draw_image(loading_images[4], WIDTH_FRAME_MENU / 2 - 80, HEIGHT_FRAME_MENU - 50);
    MLV_actualise_window();

    party->image_heart_full = MLV_load_image(PATH_IMG_HEART_FULL);
    party->image_heart_empty = MLV_load_image(PATH_IMG_HEART_EMPTY);

    if (verbose_flag)
    {
        printf("\tImages loaded\n");
    }

    if (verbose_flag)
    {
        printf("--------------------------------\n");
    }

    free_img_loading(loading_images);

    end = clock();
    if (verbose_flag)
    {
        printf("Time to load: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    return party;
}

/**
 * @brief load images for loading screen
 *
 * @param loading_images
 * @return int
 */
int init_img_loading(MLV_Image *loading_images[])
{
    for (int i = 0; i < NB_IMG_LOADING; i++)
    {
        char path_img_loading[100];
        sprintf(path_img_loading, "%s/loading%d.png", PATH_IMG_LOADING, i);
        loading_images[i] = MLV_load_image(path_img_loading);
    }
    return 0;
}

void free_img_loading(MLV_Image *loading_images[])
{
    for (int i = 0; i < NB_IMG_LOADING; i++)
    {
        MLV_free_image(loading_images[i]);
    }
}

/**
 * @brief Initialize 2 scenery for scrolling background and foreground
 *
 * @param party
 * @param loading_images
 * @return int
 */
int init_scenery(Party *party, MLV_Image *loading_images[])
{
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

    MLV_draw_image(loading_images[2], WIDTH_FRAME_MENU / 2 - 80, HEIGHT_FRAME_MENU - 50);
    MLV_actualise_window();

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
    party->scenery2->scroll = 1;
    party->scenery2->speed = SPEED_BG_GAME;

    return EXIT_SUCCESS;
}

void free_sceneries(Party *party)
{
    if (party->verbose_flag)
    {
        printf("free_sceneries\n");
    }
    MLV_free_image(party->scenery1->background->image);
    MLV_free_image(party->scenery1->foreground->image);
    free(party->scenery1->background->position);
    free(party->scenery1->background);
    free(party->scenery1->foreground->position);
    free(party->scenery1->foreground);
    free(party->scenery1);
    MLV_free_image(party->scenery2->background->image);
    MLV_free_image(party->scenery2->foreground->image);
    free(party->scenery2->background->position);
    free(party->scenery2->background);
    free(party->scenery2->foreground->position);
    free(party->scenery2->foreground);
    free(party->scenery2);
}

/**
 * @brief Initialize the menu
 *
 * @param party
 * @return int
 */
int init_menu(Party *party)
{
    party->menu = malloc(sizeof(Menu));
    party->menu->background = malloc(sizeof(Background));
    party->menu->background->position = malloc(sizeof(Position));
    party->menu->background->position->x = 0;
    party->menu->background->position->y = 0;
    party->menu->background->image = MLV_load_image(PATH_IMG_BG_MENU);
    party->menu->font_text = MLV_load_font(PATH_FONT_MENU, 50);
    party->menu->font_text_credits = MLV_load_font(PATH_FONT_MENU, 20);

    party->menu->font_title = MLV_load_font(PATH_FONT_MENU, 76);
    party->menu->img_sound_on = MLV_load_image(PATH_IMG_SOUND_ON);
    party->menu->img_sound_off = MLV_load_image(PATH_IMG_SOUND_OFF);

    return EXIT_SUCCESS;
}

void free_menu(Party *party)
{
    if (party->verbose_flag)
    {
        printf("free_menu\n");
    }
    MLV_free_image(party->menu->background->image);
    MLV_free_font(party->menu->font_text);
    MLV_free_font(party->menu->font_title);
    MLV_free_font(party->menu->font_text_credits);
    MLV_free_image(party->menu->img_sound_on);
    MLV_free_image(party->menu->img_sound_off);
    free(party->menu->background->position);
    free(party->menu->background);
    free(party->menu);
}

/**
 * @brief Initialize the scoreboard
 *
 * @param party
 * @return int
 */
int init_scoreboard(Party *party)
{
    for (int i = 0; i < MAX_BEST_SCORE; i++)
    {
        party->scoreboard[i] = malloc(sizeof(Scoreboard));
        party->scoreboard[i]->name = malloc(sizeof(char) * 20);
        party->scoreboard[i]->date = malloc(sizeof(char) * 20);
        party->scoreboard[i]->time = malloc(sizeof(char) * 20);
        party->scoreboard[i]->score = 0;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief add a score to the scoreboard
 *
 * @param party
 * @return int
 */
int insert_scoreboard(Party *party)
{
    time_t current_time;
    struct tm *time_info;
    char time_string[20];
    char date_string[20];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);
    strftime(date_string, sizeof(date_string), "%d/%m/%Y", time_info);

    Scoreboard *newScore = malloc(sizeof(Scoreboard));
    newScore->name = malloc(sizeof(char) * 20);
    newScore->date = malloc(sizeof(char) * 20);
    newScore->time = malloc(sizeof(char) * 20);

    if (strcmp(party->player->name, "\0") == 0)
    {
        strcpy(newScore->name, "Player");
    }
    else
    {
        strcpy(newScore->name, party->player->name);
    }
    strcpy(newScore->date, date_string);
    strcpy(newScore->time, time_string);
    newScore->score = party->score;

    party->scoreboard[MAX_BEST_SCORE] = newScore;

    sort_scoreboard(party);

    return EXIT_SUCCESS;
}

/**
 * @brief Sort the scoreboard
 *
 * @param party
 * @return int
 */
int sort_scoreboard(Party *party)
{
    for (int i = MAX_BEST_SCORE; i > 0; i--)
    {
        if (party->scoreboard[i]->score > party->scoreboard[i - 1]->score)
        {
            Scoreboard *temp = party->scoreboard[i];
            party->scoreboard[i] = party->scoreboard[i - 1];
            party->scoreboard[i - 1] = temp;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Write the scoreboard in a file
 *
 * @param party
 * @return int
 */
int write_scoreboard(Party *party)
{
    FILE *file = fopen(PATH_SCORE, "w");

    time_t current_time;
    struct tm *time_info;
    char time_string[20];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%Y/%m/%d %H:%M:%S", time_info);
    if (file == NULL)
    {
        fprintf(stderr, "Error: can't open file %s\n", PATH_SCORE);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < MAX_BEST_SCORE; i++)
    {
        if (party->scoreboard[i]->score != 0)
        {
            fprintf(file, "%s %ld %s %s\n", party->scoreboard[i]->name, party->scoreboard[i]->score, party->scoreboard[i]->date, party->scoreboard[i]->time);
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

/**
 * @brief Read the scoreboard from a file
 *
 * @param party
 * @return int
 */
int read_scoreboard(Party *party)
{
    FILE *file = fopen(PATH_SCORE, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: can't open file %s\n", PATH_SCORE);
        return EXIT_FAILURE;
    }

    char name[20];
    long score;
    char time_string[20];
    char date_string[20];
    int i = 0;
    while (fscanf(file, "%s %ld %s %s", name, &score, date_string, time_string) == 4 && i < 9)
    {
        strcpy(party->scoreboard[i]->name, name);
        party->scoreboard[i]->score = score;
        strcpy(party->scoreboard[i]->date, date_string);
        strcpy(party->scoreboard[i]->time, time_string);
        i++;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

/**
 * @brief Print the scoreboard
 *
 * @param party
 * @return int
 */
int print_scoreboard(Party *party)
{
    printf("Scoreboard:\n");
    for (int i = 0; i < MAX_BEST_SCORE; i++)
    {
        if (party->scoreboard[i]->score != 0)
        {
            printf("%s %ld %s %s\n", party->scoreboard[i]->name, party->scoreboard[i]->score, party->scoreboard[i]->date, party->scoreboard[i]->time);
        }
    }
    return EXIT_SUCCESS;
}

/**
 * @brief generate a bonus or a penalty randomly
 *
 * @param party
 */
void generate_bonus_or_penalty(Party *party)
{
    int random_type = rand() % 2;

    if (random_type == 0)
    {
        add_bonus(party);
        if (party->verbose_flag)
        {
            printf("Bonus created\n");
        }
    }
    else
    {
        add_penalty(party);
        if (party->verbose_flag)
        {
            printf("Penalty created\n");
        }
    }
}

/**
 * @brief free the scoreboard
 *
 * @param party Structure de la partie
 * @return void
 */
void free_scoreboard(Party *party)
{
    if (party->verbose_flag)
    {
        printf("free_scoreboard\n");
    }

    for (int i = 0; i < MAX_BEST_SCORE; i++)
    {
        free(party->scoreboard[i]->name);
        free(party->scoreboard[i]->date);
        free(party->scoreboard[i]->time);
        free(party->scoreboard[i]);
    }
}

/**
 * @brief free the party
 *
 * @param party
 * @return int
 */
int free_party(Party *party)
{
    if (party->verbose_flag)
    {
        printf("free_party\n");
    }

    free_bonus(party);
    free_penalty(party);
    free_bullet_enemy(party);
    free_bullet_player(party);
    free_enemies(party);
    free_menu(party);
    free_sceneries(party);
    free_scoreboard(party);

    if (party->verbose_flag)
    {
        printf("free image and font from party\n");
    }

    MLV_free_font(party->text_game);
    MLV_free_image(party->image_heart_full);
    MLV_free_image(party->image_heart_empty);
    MLV_free_image(party->image_bullet_player);
    free(party);
    return EXIT_SUCCESS;
}
