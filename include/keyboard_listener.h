#ifndef __KEYBOARD_LISTENER__
#define __KEYBOARD_LISTENER__

#include "../include/struct.h"

int init_pressed_key(Pressed_key pk);
int detect_key_pressed(Pressed_key pk);
int print_key_pressed(Pressed_key pk);

#endif