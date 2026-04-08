#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "cpu/idt.h"
#include "cpu/irq.h"

#define MAX_INPUT 256

char input[MAX_INPUT];
int pos = 0;

// simple string compare
int starts_with(char *a, char *b)
{
    int i = 0;
    while(b[i])
    {
        if(a[i] != b[i]) return 0;
        i++;
    }
    return 1;
}

void process_command()
{
    if(starts_with(input, "help"))
    {
        print_string("\nCommands:\n");
        print_string("help  - show commands\n");
        print_string("clear - clear screen\n");
        print_string("about - OS info\n");
    }
    else if(starts_with(input, "clear"))
    {
        clear_screen();
    }
    else if(starts_with(input, "about"))
    {
        print_string("\nZenithOS v1.0\n");
    }
    else if(input[0] != 0)
    {
        print_string("\nUnknown command: ");
        print_string(input);
        print_string("\n");
    }

    pos = 0;
    input[0] = 0;
}

void kernel_main()
{
    clear_screen();

    print_string("ZenithOS v1.0\n");

    print_string("[1] Screen initialized\n");

    print_string("[2] Loading IDT...\n");
    idt_init();
    print_string("[2] IDT loaded\n");

    print_string("[3] Initializing IRQ...\n");
    irq_init();
    print_string("[3] IRQ initialized (masked)\n");

    print_string("[4] Enabling interrupts...\n");
    asm volatile("sti");
    print_string("[4] Interrupts enabled\n");

    print_string("[5] Shell ready\n");
    print_string("> ");

    while(1)
    {
        char c = keyboard_read();

        if(!c) continue;

        // ENTER
        if(c == '\n' || c == '\r')
        {
            input[pos] = 0;
            process_command();
            print_string("> ");
            continue;
        }

        // BACKSPACE
        if(c == '\b')
        {
            if(pos > 0)
            {
                pos--;
                print_string("\b \b");
            }
            continue;
        }

        // prevent overflow
        if(pos >= MAX_INPUT - 1) continue;

        input[pos++] = c;

        char str[2] = {c, 0};
        print_string(str);
    }
}