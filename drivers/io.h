#ifndef IO_H
#define IO_H

// I/O Ports
#define TTY_COMMAND_PORT        0x3D4
#define TTY_DATA_PORT           0x3D5

// I/O Port Commands
#define TTY_HIGH_BYTE_COMMAND   14
#define TTY_LOW_BYTE_COMMAND    15

// Function wrapper of out asm instruction
// Write a byte to I/O port
void outb(unsigned short port, unsigned char data);
// Read a byte from I/O port
unsigned char inb(unsigned short port);

#endif