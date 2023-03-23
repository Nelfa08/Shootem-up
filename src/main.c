/* Include des librairies C */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Include de la libMLV*/
#include <MLV/MLV_all.h>

/* Include des fichier .h */
#include "../include/window.h"
#include "../include/const.h"

/* vocabulaire : 
    - frame : aspect de la fenetre à un moment T 
    - window : fenetre d'affichage
*/
int main()
{
    int end_game = 0;
    int time_frame;

    MLV_Event event;
    MLV_Keyboard_button key;
    MLV_Button_state state;

    /* permet de récupérer les temps de début et de fin (pour vérifier si la frame est pas trop rapide)*/
    struct timespec start_time, end_time;
    /* création de la frame */
    init_window();
    /*
    Faire un draw menu ou on peut quitter le jeu ou jouer (peut etre choisir un niveau ??)
    Pour faire ca, on écrit du texte à x et y pixel, et quand on clique sur le texte avec la souris, soit on quitte, soit on lance le jeu
    (améliorations : au survole de la souris sur le texte, mettre un encadré ou qqch du genre)
    */
    while (end_game == 0)
    {
        /* Récupération de l'heure au début */
        clock_gettime(CLOCK_REALTIME, &start_time);

        /* Ici le code */
        /* Il faut refresh la frame */

        /* je ne sais pas comment on récupère les différentes touches du clavier */
        /* Proposition : on se déplace avec les flèches clavier + on tire avec la touche espace */
        event = MLV_get_event(&key, NULL, NULL, NULL,NULL,NULL,NULL,NULL, &state);
        draw_window();

        /* En fonction de l'event il faut faire des choses...*/

        /* Récupération de l'heure en fin */
        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);
        /* Si la frame a été trop vite, on attend un peu */
        if (time_frame < (1.0 / 48.0))
        {
            MLV_wait_seconds((int)(((1.0 / 48.0) - time_frame) * 1000));
            end_game = 1;
        }
    }

    /* libération mémoire frame */
    free_window();
    return 0;
}