static inline void outb(unsigned short port, unsigned char val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void timer_handler()
{
    outb(0x20, 0x20);
}