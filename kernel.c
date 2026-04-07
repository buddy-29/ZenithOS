#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "cpu/idt.h"
#include "cpu/irq.h"

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

    print_string("[5] Keyboard polling ready\n");
    print_string("> ");

    while(1)
    {
        char c = keyboard_read();

        if(c)
        {
            char str[2] = {c, 0};
            print_string(str);
        }
    }
}