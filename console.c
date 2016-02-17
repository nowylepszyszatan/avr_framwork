#include "console.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include <string.h>

typedef struct command_map_t
{
    char* commands[CONSOLE_NUM_COMMANDS];
    command_handler handlers[CONSOLE_NUM_COMMANDS];
} command_map_t;

static char s_buffer[CONSOLE_CMD_BUFFER_SIZE];
static uint8_t s_buff_index = 0;
static uint8_t s_command_index = 0;
static struct command_map_t s_command_map;

static void USARTWriteChar(const char data)
{
    while (!(UCSRA & (1 << UDRE)))
    {
    }

    UDR = data;
}

static void USARTWriteString(const char* data)
{
    uint8_t i = 0;
    
    while (data[i] != '\0')
    {
        USARTWriteChar(data[i]);
        i++;
    }
}

static void byteHandler(char c)
{
    // change newline to string terminatot
    if (c == '\r')
        c = '\0';

    s_buffer[s_buff_index++] = c;
}

static void lineHandler()
{
    s_buff_index = 0;

    // find a handler with mathing command and execute it
    uint8_t i = 0;
    for (i = 0; i < s_command_index; i++)
    {
        if (strcmp(s_command_map.commands[i], s_buffer) == 0)
        {
            s_command_map.handlers[i]();
            break;
        }
    }

    console_prompt();
}

void console_init(uint16_t ubrr_value)
{
    memset(s_buffer, '\0', CONSOLE_CMD_BUFFER_SIZE);
    s_buff_index = 0;

    // set bound rate
    UBRRL = ubrr_value;
    UBRRH = (ubrr_value >> 8);

    // set frame format:
    // - asynchronus
    // - no parity
    // - 1 stop bit
    UCSRC = (1 << URSEL)  | (3 << UCSZ0);

    // Start reciever and transimtter:
    UCSRB = (1 << RXEN) | (1 << TXEN);

    // Enable RX interrupt
    UCSRB |= (1 << RXCIE);
}

void console_printc(const char c)
{
    USARTWriteChar(c);
}

void console_prints(const char* text)
{
    USARTWriteString(text);
}

void console_println(const char* text)
{
    USARTWriteString(text);
    USARTWriteString("\r\n");
}

void console_prompt()
{
    console_prints("AVR > ");
}

void console_register_handler(char* command, command_handler fun)
{
    if (s_command_index < CONSOLE_NUM_COMMANDS)
    {
        s_command_map.commands[s_command_index] = command;
        s_command_map.handlers[s_command_index] = fun;

        s_command_index++;
    }
}


// RX interrupt rutine
ISR(USART_RXC_vect)
{
    // get the input
    volatile char recieved = UDR;
    
    // echo it back
    USARTWriteChar(recieved);

    // add char to stream
    byteHandler(recieved);

    if (recieved == '\r')
        lineHandler();
}


