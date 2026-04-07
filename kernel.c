#include "drivers/screen.h"
#include "cpu/idt.h"

void kernel_main()
{
    clear_screen();

    print_string("ZenithOS v1.0\n");
    print_string("Loading IDT...\n");

    idt_init();

    print_string("IDT Loaded\n");

    while(1);
}
