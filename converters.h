#pragma once

#include <stdint.h>

typedef char TByteBuffer[5];
typedef char TIntBuffer[7];

void byte_to_hex(uint8_t num, TByteBuffer buffer);
void int_to_hex(uint16_t num, TIntBuffer buffer);

uint8_t hex_to_byte(char* hex);
uint16_t hex_to_int(char* hex);


