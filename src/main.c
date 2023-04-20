/* Include des librairies C */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    Pressed_key pk;
    Player *player;
    Party *party;
    MLV_Music *music;

    /* Permet de récupérer les temps de début et de fin (pour vérifier si la frame est pas trop rapide) */
    struct timespec start_time, end_time;
    int time_frame;

    /* Variable pour récupérer les arguments */
    int opt;
    int verbose_flag = 0;

    /* Variables pour récupérer la position de la souris */
    int x, y;

    /* Variables pour le son */
    int border_sound = 10;
    int state_sound = 1;

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

    init_window_menu();

    /* Initialisation de la party */
    party = init_party();
    player = create_player();
    init_pressed_key(pk);
    /* Création de la frame */
    /*
    Faire un draw_menu() ou on peut quitter le jeu ou jouer (peut etre choisir un niveau ??)
    Pour faire ca, on écrit du texte à x et y pixel, et quand on clique sur le texte avec la souris, soit on quitte, soit on lance le jeu
    (améliorations : au survole de la souris sur le texte, mettre un encadré ou qqch du genre)
    */

   /* Initialisation de la musique */
    if (MLV_init_audio())
    {
        fprintf(stderr, "Audio initialisation failed");
        exit(1);
    }
    /* Chargement de la musique */
    music = MLV_load_music(PATH_MUSIC_MENU);
    MLV_play_music(music, VOL_MUSIC_MENU, -1);

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
            draw_window_menu(state_sound, border_sound);
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
                if (state_sound == 1)
                {
                    if (verbose_flag)
                    {
                        printf("Sound off\n");
                    }
                    state_sound = 0;
                    MLV_stop_music();
                }
                else
                {
                    if (verbose_flag)
                    {
                        printf("Sound on\n");
                    }
                    state_sound = 1;
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
    while (party->state == 2)
    {
        /* Récupération de l'heure au début */
        clock_gettime(CLOCK_REALTIME, &start_time);

        /* refresh de la window */
        clear_window();
        draw_frame_game(player);
        /* je ne sais pas comment on récupère les différentes touches du clavier */
        /* Proposition : on se déplace avec les flèches clavier + on tire avec la touche espace */
        MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
        if (state == MLV_PRESSED || state == MLV_RELEASED)
        {
            detect_key_pressed(pk);
            player = move_player(player, pk);
            if (verbose_flag == 1)
            {
                print_key_pressed(pk);
                printf("Player position: %d, %d\n", player->position->x, player->position->y);
            }
        }
        /* refresh de la window */

        /* En fonction de l'event il faut faire des choses... */
        /*  vérification que le joueur ne sort pas de l'écran. S'il est encore sur l'écran :
            if flèche de gauche => déplacement à gauche (player.position.x-5)
            if flèche de droite => déplacement à droite (player.position.x+5)
            if flèche du haut => déplacement vers le haut (player.position.y-5)
            if flèche du bas => déplacement vers le bas (player.position.y+5)
        */

        /* Récupération de l'heure en fin */
        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        /* Si la frame a été trop vite, on attend un peu */
        if (time_frame < (1.0 / 120.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 120.0) - time_frame) * 1000));
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
        free_player(player);
        free_window();
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}