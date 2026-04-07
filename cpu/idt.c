#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void load_idt(uint32_t);
extern void isr0();
extern void isr32();

static void idt_set_gate(int n, uint32_t handler)
{
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init()
{
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint32_t)&idt;

    // ⭐ fill ALL entries first
    for(int i = 0; i < 256; i++)
        idt_set_gate(i, (uint32_t)isr0);

    // CPU exceptions
    idt_set_gate(0, (uint32_t)isr0);

    // IRQ0 timer (after PIC remap)
    idt_set_gate(32, (uint32_t)isr32);

    load_idt((uint32_t)&idtp);
}