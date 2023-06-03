#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"

#include "../include/keyboard_listener.h"

int detect_key_pressed(Pressed_key pk)
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED)
    {
        pk[0] = 1;
    }
    else
    {
        pk[0] = 0;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)
    {
        pk[1] = 1;
    }
    else
    {
        pk[1] = 0;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)
    {
        pk[2] = 1;
    }
    else
    {
        pk[2] = 0;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)
    {
        pk[3] = 1;
    }
    else
    {
        pk[3] = 0;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED)
    {
        pk[4] = 1;
    }
    else
    {
        pk[4] = 0;
    }

    return EXIT_SUCCESS;
}

int print_key_pressed(Pressed_key pk)
{
    printf("UP: %d, RIGHT: %d, DOWN: %d, LEFT: %d, SPACE: %d\n", pk[0], pk[1], pk[2], pk[3], pk[4]);
    return EXIT_SUCCESS;
}