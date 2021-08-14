#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "vga.h"
#include "../utils/string.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;	// Get address of terminal buffer
	// Loop through entire buffer and clear it
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_scrolldown(void)
{
	terminal_row--;
	// Go through entire terminal buffer
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;

			if (y <= VGA_HEIGHT - 1)
				terminal_buffer[index] = terminal_buffer[index + VGA_WIDTH];
			else
				terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	// Newline implementation
	if (c == '\n') {
		if (++terminal_row >= VGA_HEIGHT)
			terminal_scrolldown();
		terminal_column = 0;
		return;
	}
	
	// Reset text column when reaching edge of width
	if (terminal_column >= VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;

		// Scroll down screen when reaching end of width and height by shifting all text up
		if (terminal_row >= VGA_HEIGHT)
			terminal_scrolldown();
	}

	terminal_putentryat(c, terminal_color, terminal_column++, terminal_row);
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}