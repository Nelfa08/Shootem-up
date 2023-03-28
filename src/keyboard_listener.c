#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"

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

    return 0;
}