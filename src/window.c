#include <MLV/MLV_all.h>

#include "../include/const.h"
#include "../include/struct.h"

/**
 * @brief initialisation de la window
 * 
 * @return int 
 */
int init_window()
{
    MLV_create_window(NAME_FRAME, NULL, WIDTH_FRAME, HEIGHT_FRAME);
    MLV_clear_window(MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
}

/**
 * @brief efface le contenu de la window
 * 
 * @return int 
 */
int clear_window()
{
    MLV_clear_window(MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
}

/**
 * @brief redessine la window
 * 
 * @param player 
 * @return int 
 */
int draw_window(Player player)
{
    MLV_Image *img;
    MLV_Image *bg1;
    MLV_Image *bg2;

    scroll_bg();
    img = MLV_load_image(player.path);
    MLV_resize_image_with_proportions(img, player.size, player.size);
    MLV_draw_image(img, player.position.x, player.position.y);
    MLV_actualise_window();
    return EXIT_SUCCESS;
}

/**
 * @brief libère en mémoire la window
 * 
 * @return int 
 */
int free_window()
{
    MLV_free_window();
    return EXIT_SUCCESS;
}