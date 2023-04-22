#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"

#include "../include/party.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/keyboard_listener.h"

/*Ici il faut mettre la création de la party
* Initialisation d'une structure party avec l'état (menu, en cours, fini), le niveau choisi, etc
*/

/* Il faut aussi initialiser le table d'ennemies et de missile (soit le mettre ici soit dans enemy.c et buller_enemy(fichier à créer))*/

Party *init_party()
{
    Party *party = malloc(sizeof(Party));
    party->state = 0;

    party->player = create_player();
    
    return party;
}

int free_party(Party *party)
{
    free(party);
    return EXIT_SUCCESS;
}