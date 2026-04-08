#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "cpu/idt.h"
#include "cpu/irq.h"


#define MAX_INPUT 256
#define HISTORY_SIZE 10

char history[HISTORY_SIZE][MAX_INPUT];
int history_count = 0;

char input[MAX_INPUT];
int pos = 0;

// simple string compare
int starts_with(char *a, char *b)
{
    int i = 0;

    while(b[i])
    {
        if(a[i] != b[i])
            return 0;
        i++;
    }

    return 1; // only if ALL matched
}
void clean_input()
{
    for(int i = 0; i < MAX_INPUT; i++)
    {
        if(input[i] == '\n' || input[i] == '\r')
        {
            input[i] = 0;
            return;
        }
    }
}

void process_command()
{
    if(starts_with(input, "help"))
    {
       print_string("\nCommands:\n");
       print_string("help  clear  about  echo  history\n");
    }
    else if(starts_with(input, "clear"))
    {
        clear_screen();
    }
    else if(starts_with(input, "about"))
    {
        print_string("\nZenithOS v1.0\n");
    }
    else if(starts_with(input, "history"))
    {
        print_string("\nCommand History:\n");
        for(int i = 0; i < HISTORY_SIZE; i++)
        {
            if(history[i][0] == 0) continue;
            print_string(history[i]);
            print_string("\n");
        }
    }

    else if(input[0]=='e' && input[1]=='c' && input[2]=='h' && input[3]=='o' && input[4]==' ')
    {
        print_string("\n");

        int i = 5;
        while(input[i])
        {
            char str[2] = {input[i], 0};
            print_string(str);
            i++;
        }

        print_string("\n");
    }
    else if(input[0] != 0)
    {
        print_string("\nUnknown command: ");
        print_string(input);
        print_string("\n");
    }

 
    for(int i = 0; i < MAX_INPUT; i++)
    {
        history[history_count][i] = input[i];
        if(input[i] == 0) break;
    }

    history_count++;
    if(history_count >= HISTORY_SIZE)
        history_count = 0;

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

	    clean_input();   

	    print_string("\n");
	    process_command();

	    print_string("> ");

	    pos = 0;
	    input[0] = 0;

	    continue;
	}

        // BACKSPACE
        if(c == '\b' || c == 127)
	{
	    if(pos > 0)
	    {
		pos--;
		input[pos] = 0;

		handle_backspace();
	    }
	    continue;
	}

        // IGNORE NON-PRINTABLE
        if(c < 32 || c > 126)
            continue;


        if(pos >= MAX_INPUT - 1)
            continue;

        // STORE + PRINT
        input[pos++] = c;

        char str[2] = {c, 0};
        print_string(str);
    }
}