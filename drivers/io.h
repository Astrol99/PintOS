#ifndef IO_H
#define IO_H

// Function wrapper of asm instructions

// Write a byte to I/O port
void outb(unsigned short port, unsigned char data);
// Read a byte from I/O port
unsigned char inb(unsigned short port);

#endif