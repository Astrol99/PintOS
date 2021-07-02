#include "../drivers/output.h"

int kmain() {
    fb_write_cell(0, 'A', 0, 3);
    fb_move_cursor(1);

    return 0;
}