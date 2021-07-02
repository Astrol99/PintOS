#define FB_GREEN     2
#define FB_DARK_GREY 8

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    char *fb = (char *)0x000B8000;  // Create frame buffer

    fb[i] = c;  // Assign character to framebuffer
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);   // Adjust background and foreground of text
}

int kmain() {
    fb_write_cell(0, 'A', 0, 3);

    return 0;
}