/* Include des librairies C */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>
#include <math.h>

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

double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}

void usage()
{
    printf("Usage: ./main [-v]\n");
}

/**
 * @brief Fonction main du projet
 *
 * @param argc Nombre d'argument passés au programme
 * @param argv Tableau des arguments passés au programme
 * @return int 0 si tout s'est bien passé. 1 sinon
 */
int main(int argc, char *argv[])
{
    /* Déclaration des structures */
    MLV_Keyboard_button key;
    MLV_Button_state state;
    MLV_Music *music;
    // Pressed_key *pk;
    // Player *player;
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

    /* Variables pour récupérer la position de la souris */
    int x, y;

    /* Variables pour le son */
    int border_sound = 10;

    /* Récupération des arguments */
    while ((opt = getopt(argc, argv, "vw")) != -1)
    {
        switch (opt)
        {
        case 'v':
            verbose_flag = 1;
            break;
        case '?':
            usage();
            return EXIT_FAILURE;
        }
    }

    /* Initialisation de la party */
    init_window_menu();
    printf("start init party\n");
    party = init_party();
    printf("end init party\n");

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
    while (party->state == 0 || party->state == 1)
    {
        if (party->state == 0)
        {
            draw_window_menu(party, border_sound);
            MLV_wait_mouse(&x, &y);
            if (x > 296 && x < 450 && y > 370 && y < 420)
            {
                /* On lance le jeu */
                if (verbose_flag)
                {
                    printf("Start game\n");
                }
                party->state = 2;
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
                party->state = 1;
            }
            else if (x > 305 && x < 488 && y > 540 && y < 590)
            {
                /* On quitte le jeu */
                party->state = 3;
            }
        }
        else if (party->state == 1)
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
                party->state = 0;
            }
        }
    }

    init_window_game();
    /* initialisation du tableau d'ennemis */
    /* initialisation du tableau de missiles */
    /* initialisation du tableau de bonus */
    while (party->state == 2)
    {
        /* Récupération de l'heure au début */
        clock_gettime(CLOCK_REALTIME, &start_time);

        /* refresh de la window */
        clear_window();
        if (normal_delay(1) < 0.05) // 0.0175
        {
            add_enemy(party->enemies);
        }
        draw_frame_game(party);
        move_scenery(party->scenery1, party->scenery2);
        move_enemies(party->enemies);
        move_bullets_player(party);
        collision_bullets_player(party);
        // collision_bullets_enemies(party);
        MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
        if (state == MLV_PRESSED || state == MLV_RELEASED)
        {
            detect_key_pressed(party->pk);
            party->player = move_player(party->player, party->pk);
            if (verbose_flag == 1)
            {
                print_key_pressed(party->pk);
                printf("Player position: %d, %d\n", party->player->position->x, party->player->position->y);
            }
        }
        if (party->pk[4] == 1)
        {
            if (party->player->delay_shoot == DELAY_SHOOT_PLAYER)
            {
                add_bullet_player(party);
                party->player->delay_shoot = DELAY_SHOOT_PLAYER;
                party->player->delay_shoot -= 1;
            } else if(party->player->delay_shoot == 0) {
                party->player->delay_shoot = DELAY_SHOOT_PLAYER;
            } else {
                party->player->delay_shoot -= 1;
            }
        } else {
            party->player->delay_shoot = DELAY_SHOOT_PLAYER;
        }

        /* Si le joueur appuie sur espace => ajouter un ennemie*/

        /* Si le joueur n'a plus de vie : il perd */
        if (party->player->health <= 0)
        {
            party->state = 3;
        }
        party->score += 1;

        /* Récupération de l'heure en fin */
        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        /* Si la frame a été trop vite, on attend un peu */
        if (time_frame < (1.0 / 48.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 48.0) - time_frame) * 1000));
        }

        /* is win ? => party->state == 3 */
    }

    if (party->state == 3)
    {
        /* On quitte le jeu */
        if (verbose_flag)
        {
            printf("End of the game\n");
            printf("Free memory\n");
        }
        MLV_stop_music();
        MLV_free_music(music);
        MLV_free_audio();
        free_party(party);
        free_window();
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}