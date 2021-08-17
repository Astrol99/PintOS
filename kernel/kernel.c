#include "../drivers/tty.h"
#include "../drivers/vga.h"
#include "../drivers/serial.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, u suck"
#endif

#if !defined(__i386__)
#error "OS needs to be compiled with ix86-elf compiler, dumbass"
#endif

void kmain(void)
{
    terminal_initialize();
    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
    terminal_writestring("Terminal initialized\n");

    serial_configure_baud_rate(SERIAL_COM1_BASE, 3);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_is_transmit_fifo_empty(SERIAL_COM1_BASE);
    
    serial_send(SERIAL_COM1_BASE, "Serial initialized");
    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK));
    terminal_writestring("Serial initialized\n");
}