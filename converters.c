#include "converters.h"

#include <stdlib.h>

void byte_to_hex(uint8_t num, byte_buffer_t buffer)
{
    buffer = "0x\0\0";

    itoa(num, buffer + 2, 16);
}

void int_to_hex(uint16_t num, int_buffer_t buffer)
{
    buffer = "0x\0\0\0\0";

    itoa(num, buffer + 2, 16);
}

uint8_t hex_to_byte(char* hex)
{
    return (uint8_t)atoi(hex + 2);
}

uint16_t hex_to_int(char* hex)
{
    return (uint16_t)atoi(hex + 2);
}

