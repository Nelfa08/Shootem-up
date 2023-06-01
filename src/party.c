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

/*Ici il faut mettre la création de la party
 * Initialisation d'une structure party avec l'état (menu, en cours, fini), le niveau choisi, etc
 */

/* Il faut aussi initialiser le table d'ennemies et de missile (soit le mettre ici soit dans enemy.c et buller_enemy(fichier à créer))*/

double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}

Party *init_party(int verbose_flag, int hitbox_flag)
{
    clock_t start, end;
    start = clock();
    if (verbose_flag)
    {
        printf("--------------------------------\n");
        printf("Party initialization started: \n");
    }
    Party *party = malloc(sizeof(Party));
    party->status = 0;
    party->sound = 0;
    party->score = 0;
    party->verbose_flag = verbose_flag;
    party->hitbox_flag = hitbox_flag;
    party->enemies_density = ENEMIES_DENSITY;

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
    if (verbose_flag)
    {
        printf("\tScenery 1 created\n");
    }

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
    if (verbose_flag)
    {
        printf("\tScenery 2 created\n");
    }

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
    if (verbose_flag)
    {
        printf("\tMenu created\n");
    }

    party->image_bullet_player = MLV_load_image(PATH_IMG_BULLET_PLAYER);
    party->image_bullet_enemy = MLV_load_image(PATH_IMG_BULLET_ENEMY);
    party->image_heart_empty = MLV_load_image(PATH_IMG_HEART_EMPTY);
    party->image_heart_full = MLV_load_image(PATH_IMG_HEART_FULL);
    party->image_shield_bonus = MLV_load_image(PATH_IMG_SHIELD_BONUS);
    party->image_speed_bonus = MLV_load_image(PATH_IMG_SPEED_BONUS);
    party->image_health_bonus = MLV_load_image(PATH_IMG_HEALTH_BONUS);
    party->image_bomb_bonus = MLV_load_image(PATH_IMG_BOMB_BONUS);
    party->image_slow_penalty = MLV_load_image(PATH_IMG_SLOW_PENALTY);
    party->image_reverse_penalty = MLV_load_image(PATH_IMG_REVERSE_PENALTY);
    party->image_damage_penalty = MLV_load_image(PATH_IMG_DAMAGE_PENALTY);
    party->image_shield = MLV_load_image(PATH_IMG_SHIELD);
    if (verbose_flag)
    {
        printf("\tImages loaded\n");
    }

    for (int i = 0; i < 10; i++)
    {
        party->scoreboard[i] = malloc(sizeof(Scoreboard));
        party->scoreboard[i]->name = malloc(sizeof(char) * 20);
        party->scoreboard[i]->date = malloc(sizeof(char) * 20);
        party->scoreboard[i]->time = malloc(sizeof(char) * 20);
    }
    if (verbose_flag)
    {
        printf("\tScoreboard created\n");
        printf("--------------------------------\n");
    }
    end = clock();
    printf("Time to load: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    return party;
}

int write_scoreboard(Party *party)
{
    FILE *file = fopen(PATH_SCORE, "a");

    time_t current_time;
    struct tm *time_info;
    char time_string[20];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%Y/%m/%d %H:%M:%S", time_info);
    printf("%s\n", time_string);
    if (file == NULL)
    {
        fprintf(stderr, "Error: can't open file %s\n", PATH_SCORE);
        return EXIT_FAILURE;
    }

    fprintf(file, "%s %ld %s\n", party->player->name, party->score, time_string);

    fclose(file);
    return EXIT_SUCCESS;
}

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
    while (fscanf(file, "%s %ld %s %s", name, &score, date_string, time_string) == 4 && i < 10)
    {
        strcpy(party->scoreboard[i]->name, name);
        party->scoreboard[i]->score = score;
        strcpy(party->scoreboard[i]->date, date_string);
        strcpy(party->scoreboard[i]->time, time_string);
        i++;
    }

    party->size_file_scoreboard = i;

    fclose(file);
    return EXIT_SUCCESS;
}
int print_scoreboard(Party *party)
{
    for (int i = 0; i < party->size_file_scoreboard; i++)
    {
        printf("%s %ld %s %s\n", party->scoreboard[i]->name, party->scoreboard[i]->score, party->scoreboard[i]->date, party->scoreboard[i]->time);
    }
    return EXIT_SUCCESS;
}

int free_party(Party *party)
{
    free_player(party->player);
    free(party);
    return EXIT_SUCCESS;
}

void generate_bonus_or_penalty(Party *party)
{
    // Génère un nombre entier aléatoire entre 0 et 1 pour sélectionner le type de bonus ou de pénalité
    int random_type = rand() % 2;
    // int random_type = 1;

    // Génère les propriétés communes à tous les bonus et pénalités

    // Crée un bonus ou une pénalité en fonction du type aléatoire généré
    if (random_type == 0)
    {
        add_bonus(party);
        printf("Bonus created\n");
    }
    else
    {
        add_penalty(party);
        printf("Penalty created\n");
    }
}