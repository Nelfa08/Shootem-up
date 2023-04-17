#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"

#include "../include/party.h"

/*Ici il faut mettre la création de la party
* Création du joueur, création de l'enemy, du niveau choisi, etc
* Initialisation d'une structure party avec l'état (menu, en cours, fini), le niveau choisi, etc
*/

Party *init_party()
{
    Party *party = malloc(sizeof(Party));
    party->state = 0;
    return party;
}

void init_pressed_key(Pressed_key pk)
{
    for (int i = 0; i < 4; i++)
    {
        pk[i] = 0;
    }
}