#include <MLV/MLV_all.h>

#include "../include/const.h"
#include "../include/struct.h"

int init_window()
{
    MLV_create_window(NAME_FRAME, NULL, WIDTH_FRAME, HEIGHT_FRAME);
    MLV_clear_window(MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
}

int clear_window()
{
    MLV_clear_window(MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
}

int draw_window(Player player)
{
    MLV_Image *img;
    img = MLV_load_image("data/ship.png");
    MLV_resize_image_with_proportions(img, player.size, player.size);
    MLV_draw_image(img, player.position.x, player.position.y);
    MLV_actualise_window();
    return EXIT_SUCCESS;
}

int free_window()
{
    MLV_free_window();
    return EXIT_SUCCESS;
}