#include <stdint.h>

static inline uint8_t inb(uint16_t port)
{
    uint8_t result;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

char keyboard_read()
{
    uint8_t scancode;

    while (!(inb(0x64) & 1));   // wait key

    scancode = inb(0x60);

    // simple mapping (numbers + letters basic)
    char map[128] =
    {
        0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
        'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\',
        'z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',
    };

    if(scancode > 57) return 0;

    return map[scancode];
}