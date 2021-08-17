#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stddef.h>
// I/O ports for serial ports
#define SERIAL_COM1_BASE                0x3F8   // COM1 base port

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

// I/O port commands for serial

// Tells serial port to expect first the highest 9 bits on the data port, then lower 8 bits will follow
#define SERIAL_LINE_ENABLE_DLAB         0x80
#define SERIAL_STD_LINE_CONFIG          0x03    // A standard value meaning: 
                                                // 8 bit length, no parity bit, one stop bit, 
                                                // and break control disabled

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
int serial_is_transmit_fifo_empty(unsigned int com);
void serial_send(unsigned int com, const char* data);

#endif