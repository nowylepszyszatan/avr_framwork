#pragma once

#include <stdint.h>

typedef char byte_buffer_t[5];
typedef char int_buffer_t[7];

void byte_to_hex(uint8_t num, byte_buffer_t buffer);
void int_to_hex(uint16_t num, int_buffer_t buffer);

uint8_t hex_to_byte(char* hex);
uint16_t hex_to_int(char* hex);


