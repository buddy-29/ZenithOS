#include "drivers/screen.h"

void kernel_main() {

    clear_screen();

    print_string("ZenithOS v1.0\n");
    print_string("Boot Successful\n\n");

    print_string("Welcome to ZenithOS Kernel");
}
