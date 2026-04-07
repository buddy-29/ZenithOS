int cursor = 0;

void print_char(char c) {
    char *video = (char*)0xb8000;

    if (c == '\n') {
        cursor += 80 - (cursor % 80);
    } else {
        video[cursor * 2] = c;
        video[cursor * 2 + 1] = 0x07;
        cursor++;
    }
}

void print_string(char *str) {
    int i = 0;
    while (str[i] != 0) {
        print_char(str[i]);
        i++;
    }
}

void clear_screen() {
    char *video = (char*)0xb8000;

    for (int i = 0; i < 80 * 25; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x07;
    }

    cursor = 0;
}
