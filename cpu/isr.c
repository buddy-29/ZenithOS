#include "../drivers/screen.h"

void isr_handler(int n)
{
    print_string("Exception triggered!\n");

    while(1);
}
