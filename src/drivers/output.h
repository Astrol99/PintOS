#ifndef INCLUDE_OUTPUT_H
#define INCLUDE_OUTPUT_H

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/** write:
 *  Writes a buffer of characters with following cursor
 *
 *  @param buf Buffer of chars to print to screen
 *  @param len Length of the buffer
 */
int write(char *buf, unsigned int len);

#endif /* INCLUDE_OUTPUT_H */