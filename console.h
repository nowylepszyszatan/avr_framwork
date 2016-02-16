#pragma once

#include <stdint.h>

typedef void (*command_handler)();

#define CONSOLE_CMD_BUFFER_SIZE 32
#define CONSOLE_NUM_COMMANDS 16

void console_prompt();

void console_init(uint16_t ubrr_value);

void console_printc( const char c);

void console_prints(const char* text);

void console_println(const char* text);

void console_register_handler(char* command, command_handler fun);





