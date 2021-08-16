#ifndef TTY_H
#define TTY_H
 
#include <stdint.h>
#include <stddef.h>

// I/O Ports
#define TTY_COMMAND_PORT        0x3D4
#define TTY_DATA_PORT           0x3D5

// I/O Port Commands
#define TTY_HIGH_BYTE_COMMAND   14
#define TTY_LOW_BYTE_COMMAND    15

void terminal_initialize(void);

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void terminal_disable_cursor(void);
uint16_t terminal_get_cursor_position(void);
void terminal_move_cursor(int x, int y);

void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
 
#endif