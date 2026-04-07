#include "../drivers/screen.h"

static inline void outb(unsigned short port, unsigned char val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void isr_handler()
{
    print_string("T");

    outb(0x20, 0x20);   // EOI
}