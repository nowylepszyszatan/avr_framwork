#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "console.h"

char* test_cmd = "test";
char* dupa_cmd = "dupa";

command_handler test_fun()
{
    console_println("hura!");
}

command_handler dupa_fun()
{
    console_println("Twoja Stara");
}

void init()
{
    DDRC = 0xFF;
    
    sei();
}


int main(void)
{
    init();
    set_sleep_mode(SLEEP_MODE_IDLE);

    // avr is set to 1MHz,
    // seting ubrr to 51 gives bound rate = 1200
    console_init(51);

    console_register_handler(dupa_cmd, &dupa_fun);
    console_register_handler(test_cmd, &test_fun);

    console_prompt();

    for(;;)
        sleep_mode();
}

