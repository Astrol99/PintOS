#include "../drivers/vga.h"

/*  vscode intellisense trippin here
#if defined(__linux__)
#error "You are not using a cross-compiler, u suck"
#endif
*/

#if !defined(__i386__)
#error "OS needs to be compiled with ix86-elf compiler, dumbass"
#endif

void kmain(void)
{
    terminal_initialize();

    terminal_writestring("Hello\nWorld!");
}