#include "serial.h"
#include "io.h"
#include "../utils/string.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_STD_LINE_CONFIG);
}

/* @return 0 if transmit FIFO queue is not empty
 *         1 if transmit FIFO queue is not empty
 */
int serial_is_transmit_fifo_empty(unsigned int com)
{
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_send(unsigned int com, const char* data)
{
    for (size_t i = 0; i < strlen(data); i++)
        outb(com, data[i]);
}