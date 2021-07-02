#include "output.h"
#include "io.h"

void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    char *fb = (char *)0x000B8000;  // Create frame buffer

    fb[i] = c;  // Assign character to framebuffer
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);   // Adjust background and foreground of text
}