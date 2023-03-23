#include <MLV/MLV_all.h>

#include "../include/const.h"

int init_window() {
    MLV_create_window(NAME_FRAME, NULL, WIDTH_FRAME, HEIGHT_FRAME);
    MLV_clear_window(MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
}

int draw_window() {
    MLV_Image *player;
    player = MLV_load_image("data/ship.png");
    MLV_resize_image_with_proportions(player, SIZE_PLAYER, SIZE_PLAYER);
    MLV_draw_image(player, 0, 0);
    MLV_actualise_window();
    return EXIT_SUCCESS;
}

int free_window() {
    MLV_free_window();
    return EXIT_SUCCESS;
}