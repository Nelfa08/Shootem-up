#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"

/**
 * @brief
 *
 * @return Player
 */
Player init_player()
{
    Player player;
    player.health = 5;
    player.size = 100;
    player.speed = 2;
    player.position.x = WIDTH_FRAME / 2 - player.size;
    player.position.y = HEIGHT_FRAME - (player.size * 2);
    player.path = "data/ship.png";
    return player;
}

Player move_player(Player player, Pressed_key pk) {
    if(pk[0] == 1) {
        if(player.position.y < 0) {
            printf("outhaut\n");
            return player;
        }
        player.position.y -= player.speed*5;
    }
    if(pk[1] == 1) {
        if(player.position.x+player.size > WIDTH_FRAME) {
            printf("outdroit\n");
            return player;
        }
        player.position.x += player.speed*5;
    }
    if(pk[2] == 1) {
        if(player.position.y+player.size > HEIGHT_FRAME) {
            printf("outbas\n");
            return player;
        }
        player.position.y += player.speed*5;
    }
    if(pk[3] == 1) {
        if(player.position.x < 0) {
            printf("outgauche\n");
            return player;
        }
        player.position.x -= player.speed*5;
    }

    return player;
}