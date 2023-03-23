#include <MLV/MLV_all.h>

void printWindow() {
    MLV_create_window("Shootem", NULL, 600, 400);
    MLV_wait_seconds(5);
    MLV_free_window();
}