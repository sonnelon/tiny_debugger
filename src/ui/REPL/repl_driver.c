#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repl_driver.h"

#define BUFFER_SIZE 1024

static inline void display_logo();
static inline void clear_screen();
static inline void display_start_info();
static int read_commands(char * buffer, int buffer_len);

int run_repl(const char * file_path) {
    clear_screen();
    display_logo();
    display_start_info();
    while (1) {
        printf("(tbg) ");
        char buffer[BUFFER_SIZE];
        read_commands(buffer, BUFFER_SIZE);
        puts(buffer);
    }

    return 0;
}

static int read_commands(char * buffer, int buffer_len) {
    int i;
    for (i = 0; i < buffer_len - 1; i++) {
        int ch = getchar();
        if (ch == '\n' || ch == EOF) break;
        buffer[i] = (char)ch;
    }
    buffer[i] = '\0';
    return 0;
}

static inline void display_logo() {
    puts("  _______ _             _____  ____   _____ ");
    puts(" |__   __(_)           |  __ \\|  _ \\ / ____|");
    puts("    | |   _ _ __  _   _| |  | | |_) | |  __ ");
    puts("    | |  | | '_ \\| | | | |  | |  _ <| | |_ |");
    puts("    | |  | | | | | |_| | |__| | |_) | |__| |");
    puts("    |_|  |_|_| |_|\\__, |_____/|____/ \\_____|");
    puts("                   __/ |                    ");
    puts("                  |___/                     ");
}

static inline void display_start_info() {
    puts("b [ADDR] --- Set a breakpoint.");
    puts("r [OPTS] --- Start a program.");
    puts("n        --- Proceed to the next step.");
    puts("s        --- Enter the function.");
    puts("h        --- Display help information.");
}

static inline void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
