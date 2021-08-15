#ifndef TTY_H
#define TTY_H
 
 #include <stdint.h>
 #include <stddef.h>
 
void terminal_initialize(void);

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void terminal_disable_cursor(void);
uint16_t terminal_get_cursor_position(void);
void terminal_move_cursor(int x, int y);

void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
 
#endif