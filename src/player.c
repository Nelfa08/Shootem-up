#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"

Player init_player()
{
    Player player;

    player.health = 5;
    player.size = 100;
    player.speed = 2;
    player.position.x = WIDTH_FRAME / 2 - player.size;
    player.position.y = HEIGHT_FRAME - (player.size * 2);

    return player;
}

Player move_player(Player player, MLV_Keyboard_button key)
{
    if (key == MLV_KEYBOARD_UP)
    {
        printf("haut\n");
        player.position.y -= 5;
    }
    else if (key == MLV_KEYBOARD_DOWN)
    {
        printf("bas\n");
        player.position.y += 5;
    }
    else if (key == MLV_KEYBOARD_RIGHT)
    {
        printf("droite\n");
        player.position.x += 5;
    }
    else if (key == MLV_KEYBOARD_LEFT)
    {
        printf("gauche\n");
        player.position.x -= 5;
    }
    else
    {
        key = MLV_NONE;
    }
    return player;
}