#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repl_driver.h"
#include "dispatcher.h"

static inline void
display_logo();

static inline void
display_start_info();

static dbg_err_t 
read_commands(char * buffer, int buffer_len);

dbg_err_t
run_repl(const char * file_path) {
    system("clear");
    display_logo();
    display_start_info();
    int buff_sz = 1024;
    while (1) {
        printf("tdb >> ");
        char buffer[buff_sz];
        read_commands(buffer, buff_sz);
        run_dispatcher(buffer, file_path);
    }

    return DBG_OK;
}

static dbg_err_t
read_commands(char * buffer, int buffer_len) {
    int i;

    for (i = 0; i < buffer_len - 1; i++) {
        int ch = getchar();
        if (ch == '\n' || ch == EOF) break;
        buffer[i] = (char)ch;
    }

    buffer[i] = '\0';
    return DBG_OK;
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
    int msgs_sz = 5;
    const char * msgs[msgs_sz] = {
        "b [ADDR] --- Set a breakpoint.",
        "r [OPTS] --- Start a program.", 
        "n        --- Proceed to the next step.",
        "s        --- Enter the function.",
        "h        --- Display help information.",
    };

    for (int i = 0; i < msgs_sz; i++) puts(msgs[i]);
}
