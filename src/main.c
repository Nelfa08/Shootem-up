/**
 * @file main.c
 * @author Corentin RODDIER Yacine DJEBLOUN
 * @brief
 * @version 1.0
 * @date 2023-05-01
 *
 * @copyright Copyright (c) 2023
 *
 */

/* Include des librairies C */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>

/* Include de la libMLV */
#include <MLV/MLV_all.h>

/* Include des fichiers d'entête */
#include "../include/window.h"
#include "../include/const.h"
#include "../include/struct.h"
#include "../include/player.h"
#include "../include/keyboard_listener.h"
#include "../include/party.h"
#include "../include/enemy.h"
#include "../include/bullet_player.h"
#include "../include/bullet_enemy.h"
#include "../include/penalty.h"
#include "../include/bonus.h"

/**
 * @brief Print usage of the program
 *
 */
void usage()
{
    printf("Usage: ./main [-v]\n");
}

/**
 * @brief Main function of the program
 *
 * @param argc Number of arguments
 * @param argv Arguments
 * @return int 0 if no error, 1 if error
 */
int main(int argc, char *argv[])
{
    /* Déclaration des structures */
    MLV_Keyboard_button key;
    MLV_Button_state state;
    MLV_Music *music;
    Party *party;

    /* Permet de récupérer les temps de début et de fin (pour vérifier si la frame est pas trop rapide) */
    struct timespec start_time, end_time;
    int time_frame;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    srand(tv.tv_sec * 1000 + tv.tv_usec / 1000);

    /* Variable pour récupérer les arguments */
    int opt;
    int verbose_flag = 0;
    int hitbox_flag = 0;

    /* Variables pour récupérer la position de la souris */
    int x, y;

    /* Récupération des arguments */
    while ((opt = getopt(argc, argv, "vh")) != -1)
    {
        switch (opt)
        {
        case 'v':
            verbose_flag = 1;
            break;
        case 'h':
            hitbox_flag = 1;
            break;
        case '?':
            usage();
            return EXIT_FAILURE;
        }
    }

    if (verbose_flag == 1)
    {
        printf("Game start with verbose_flag\n");
        if (hitbox_flag == 1)
        {
            printf("Game start with hitbox_flag\n");
        }
        printf("\n");
    }

    /* Initialisation de la party */
    init_window_menu();
    party = init_party(verbose_flag, hitbox_flag);

    /* Initialisation de la musique */
    if (MLV_init_audio())
    {
        fprintf(stderr, "Audio initialisation failed\n");
        exit(1);
    }
    /* Chargement de la musique */
    music = MLV_load_music(PATH_MUSIC_MENU);
    if (party->sound == 1)
    {
        MLV_play_music(music, VOL_MUSIC_MENU, -1);
    }

    /* Différents états de la partie :
     * 0 : menu
     * 1 : crédits
     * 2 : jeu
     * 3 : fin
     */
    while (party->status == 0 || party->status == 1)
    {
        if (party->status == 0)
        {
            draw_window_menu(party);
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED)
            {
                MLV_get_mouse_position(&x, &y);
                if (x > 296 && x < 450 && y > 370 && y < 420)
                {
                    /* On lance le jeu */
                    if (verbose_flag)
                    {
                        printf("Start game\n");
                    }
                    party->status = 2;
                }
                else if (x > WIDTH_FRAME_MENU - (SIZE_ICON_MUSIC + 10) && x < (WIDTH_FRAME_MENU - 10) && y > 10 && y < SIZE_ICON_MUSIC + 10)
                {
                    if (party->sound == 1)
                    {
                        if (verbose_flag)
                        {
                            printf("Sound off\n");
                        }
                        party->sound = 0;
                        MLV_stop_music();
                    }
                    else
                    {
                        if (verbose_flag)
                        {
                            printf("Sound on\n");
                        }
                        party->sound = 1;
                        MLV_play_music(music, VOL_MUSIC_MENU, -1);
                    }
                }
                else if (x > 257 && x < 488 && y > 450 && y < 500)
                {
                    /* On affiche les crédits */
                    if (verbose_flag)
                    {
                        printf("Print credits\n");
                    }
                    party->status = 1;
                }
                else if (x > 305 && x < 488 && y > 540 && y < 590)
                {
                    /* On quitte le jeu */
                    party->status = 3;
                }
            }
        }
        else if (party->status == 1)
        {
            clear_window();
            draw_window_credits();
            MLV_wait_mouse(&x, &y);
            if (x > 0 && x < 105 && y > 0 && y < 40)
            {
                /* On revient au menu */
                if (verbose_flag)
                {
                    printf("Back to menu\n");
                }
                party->status = 0;
            }
        }
    }

    init_window_game();

    /* initialisation du tableau d'ennemis */
    /* initialisation du tableau de missiles */
    /* initialisation du tableau de bonus */
    while (party->status == 2)
    {
        /* Récupération de l'heure au début */
        clock_gettime(CLOCK_REALTIME, &start_time);
        /* refresh de la window */
        clear_window();
        if (normal_delay(1) < 0.01)
        {
            add_enemy(party);
        }
        draw_frame_game(party);
        move_scenery(party->scenery1, party->scenery2);
        move_enemies(party);
        move_bullets_player(party);
        player_kill_ennemy(party);
        fire_enemy(party);
        move_bullets_enemy(party);
        enemy_kill_player(party);
        move_bonus(party);
        move_penalty(party);
        player_get_bonus(party);
        player_get_penalty(party);
        MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
        detect_key_pressed(party->pk);
        move_player(party->player, party->pk);
        // if (verbose_flag == 1)
        // {
        //     // print_key_pressed(party->pk);
        //     printf("Player position: %d, %d\n", party->player->position->x, party->player->position->y);
        // }
        if (party->pk[4] == 1)
        {
            party->player->sprite_attack->status = 1;
            party->player->sprite_walk->status = 0;
            if (party->player->delay_shoot == DELAY_SHOOT_PLAYER)
            {
                add_bullet_player(party);
                party->player->delay_shoot = DELAY_SHOOT_PLAYER;
                party->player->delay_shoot -= 1;
            }
            else if (party->player->delay_shoot == 0)
            {
                party->player->delay_shoot = DELAY_SHOOT_PLAYER;
            }
            else
            {
                party->player->delay_shoot -= 1;
            }
        }
        else
        {
            party->player->delay_shoot = DELAY_SHOOT_PLAYER;
            party->player->sprite_attack->current_frame = 0;
            party->player->sprite_attack->status = 0;
            party->player->sprite_walk->status = 1;
        }

        /* Si le joueur n'a plus de vie : il perd */
        if (party->player->health <= 0)
        {
            party->status = 3;
        }

        /* Incrémentation du score */
        party->score += 1;

        if (party->score % 500 == 0)
        {
            generate_bonus_or_penalty(party);
        }

        /* Récupération de l'heure en fin */
        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        /* Si la frame a été trop vite, on attend un peu */
        if (time_frame < (1.0 / 60.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 60.0) - time_frame) * 1000));
        }

        /* is win ? => party->status == 3 */
    }

    if (party->status == 3)
    {
        /* Fin du jeu */

        /* Pour le fin du jeu :
            On reste sur l'écran de jeu de la partie et on affiche un champs pour demander le nom du joueur + son score.
            Une fois le nom renseigné, on stocke le score dans un fichier et on affiche le classement des meilleurs scores + (bonus) on affiche son classement
        */
        /* draw_input_name = */

        draw_input_name(party);
        write_scoreboard(party);
        read_scoreboard(party);
        print_scoreboard(party);
        return EXIT_SUCCESS;

        draw_window_end(party);
        printf("End of the game\n");
        printf("Score : %ld\n", party->score);
    }
    if (verbose_flag)
    {
        printf("End of the game\n");
        printf("Free memory\n");
    }
    free(party->player->name); // voir la doc du bloc de MLV_wait_input_box_with_font
    MLV_stop_music();
    MLV_free_music(music);
    MLV_free_audio();
    free_party(party);
    free_window();
    return EXIT_SUCCESS;
}