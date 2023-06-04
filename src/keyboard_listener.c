/**
 * @file keyboard_listener.c
 * @author Corentin RODDIER and Yacine DJEBLOUN
 * @brief File containing all the functions about the keyboard listener
 * @version 1.0
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/const.h"

#include "../include/keyboard_listener.h"

/**
 * @brief Detect if a key is pressed and return the result in an array pk[0] = up, pk[1] = right, pk[2] = down, pk[3] = left, pk[4] = space
 * 
 * @param pk 
 * @return int 
 */
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