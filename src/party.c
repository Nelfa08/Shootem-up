#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"

/*Ici il faut mettre la création de la party
* Création du joueur, création de l'enemy, du niveau choisi, etc
* Initialisation d'une structure party avec l'état (menu, en cours, fini), le niveau choisi, etc
*/

void init_pressed_key(Pressed_key pk) {
    for (int i = 0; i < 4; i++)
    {
        pk[i] = 0;
    }
}