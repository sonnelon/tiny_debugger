#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repl_driver.h"
#include "dispatcher.h"

#define BUFFER_SIZE 1024
#define HELP_MSGS_COUNT 5

static inline void
display_logo();

static inline void
clear_screen();

static inline void
display_start_info();

static int
read_commands(char * buffer, int buffer_len);

int
run_repl() {
    clear_screen();
    display_logo();
    display_start_info();
    while (1) {
        printf("(tdb) ");
        char buffer[BUFFER_SIZE];
        read_commands(buffer, BUFFER_SIZE);
        run_dispatcher(buffer);
    }

    return 0;
}

static int
read_commands(char * buffer, int buffer_len) {
    int i;
    for (i = 0; i < buffer_len - 1; i++) {
        int ch = getchar();
        if (ch == '\n' || ch == EOF) break;
        buffer[i] = (char)ch;
    }
    buffer[i] = '\0';
    return 0;
}

static inline void 
display_logo() {
    puts("  _______ _             _____  ____   _____ ");
    puts(" |__   __(_)           |  __ \\|  _ \\ / ____|");
    puts("    | |   _ _ __  _   _| |  | | |_) | |  __ ");
    puts("    | |  | | '_ \\| | | | |  | |  _ <| | |_ |");
    puts("    | |  | | | | | |_| | |__| | |_) | |__| |");
    puts("    |_|  |_|_| |_|\\__, |_____/|____/ \\_____|");
    puts("                   __/ |                    ");
    puts("                  |___/                     ");
}

static inline void
display_start_info() {
    const char * msgs[HELP_MSGS_COUNT] = {
        "b [ADDR] --- Set a breakpoint.",
        "r [OPTS] --- Start a program.", 
        "n        --- Proceed to the next step.",
        "s        --- Enter the function.",
        "h        --- Display help information.",
    };

    for (int i = 0; i < HELP_MSGS_COUNT; i++) puts(msgs[i]);
}

static inline void
clear_screen() { system("clear"); }
