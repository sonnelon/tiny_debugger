#include <stdio.h>
#include <stdlib.h>
#include "repl_driver.h"

static inline void display_logo();
static inline void clean_stdin();
static inline void clear_screen();

int run_repl(const char * file_path) {
    clear_screen();
    display_logo();
    while (1) {
        printf("(tbg) ");
        char s;
        scanf("%c", &s);
        clean_stdin();
    }

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

static inline void clean_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static inline void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
