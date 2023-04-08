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
    MLV_Keyboard_button key;
    MLV_Button_state state;
    Player *player;
    Pressed_key pk;

    /* Permet de récupérer les temps de début et de fin (pour vérifier si la frame est pas trop rapide) */
    struct timespec start_time, end_time;

    int end_game = 0;
    int time_frame;
    int opt;
    int verbose_flag = 0;

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

    /* Création de la frame */
    init_window();

    /* Initialisation de la game (création du player plus peut etre d'autres choses) */
    player = create_player();
    init_pressed_key(pk);
    /*
    Faire un draw_menu() ou on peut quitter le jeu ou jouer (peut etre choisir un niveau ??)
    Pour faire ca, on écrit du texte à x et y pixel, et quand on clique sur le texte avec la souris, soit on quitte, soit on lance le jeu
    (améliorations : au survole de la souris sur le texte, mettre un encadré ou qqch du genre)
    */
    while (end_game == 0)
    {
        /* Récupération de l'heure au début */
        clock_gettime(CLOCK_REALTIME, &start_time);

        /* refresh de la window */
        clear_window();
        draw_window(player);
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
                printf("pos_player: %d, %d\n", player->position->x, player->position->y);
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
        if (time_frame < (1.0 / 48.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 48.0) - time_frame) * 1000));
        }
    }

    /* libération mémoire window */
    free_window();
    return EXIT_SUCCESS;
}