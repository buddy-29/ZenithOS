#include "drivers/screen.h"
#include "cpu/idt.h"
#include "cpu/irq.h"

void kernel_main()
{
    clear_screen();

    print_string("ZenithOS v1.0\n");

    print_string("Loading IDT...\n");
    idt_init();

    print_string("Remapping PIC...\n");
    irq_init();

    print_string("IRQ Ready\n");

    while(1);
}