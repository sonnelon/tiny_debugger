#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repl_driver.h"
#include "repl_dispatcher.h"

static inline void display_logo ();
static inline void display_start_info ();
static dbg_err_t read_commands (char * buffer, int buffer_len);

dbg_err_t repl_run (const char * file_path, struct dbg_t * dbg, volatile sig_atomic_t * want_exit) 
{
    system("clear");
    display_logo();
    display_start_info();

    int buff_sz = 1024;
    while (1 && !(*want_exit)) 
	{
        printf("tdb >> ");
        char buffer[buff_sz];
        read_commands(buffer, buff_sz);
        repl_run_dispatcher(dbg, buffer, file_path);
    }

    return DBG_OK;
}

static dbg_err_t read_commands (char * buffer, int buffer_len) 
{
    int i;
    for (i = 0; i < buffer_len - 1; i++) 
	{
        int ch = getchar();
        if (ch == '\n' || ch == EOF) break;
        buffer[i] = (char)ch;
    }

    buffer[i] = '\0';
    return DBG_OK;
}

static inline void display_logo () 
{
    puts("  _______ _             _____  ____   _____ ");
    puts(" |__   __(_)           |  __ \\|  _ \\ / ____|");
    puts("    | |   _ _ __  _   _| |  | | |_) | |  __ ");
    puts("    | |  | | '_ \\| | | | |  | |  _ <| | |_ |");
    puts("    | |  | | | | | |_| | |__| | |_) | |__| |");
    puts("    |_|  |_|_| |_|\\__, |_____/|____/ \\_____|");
    puts("                   __/ |                    ");
    puts("                  |___/                     ");
}

static inline void display_start_info () 
{
    const char * msgs[] = {
        "b      [ADDR]    Set a breakpoint.",
        "r/run  [OPTS]    Start a program.", 
        "n/next           Proceed to the next step.",
        "s/step           Enter the function.",
        "h/help           Display help information.",
    };
	
	const int msgs_len = sizeof(msgs)/sizeof(msgs[0]);
    for (int i = 0; i < msgs_len; i++) puts(msgs[i]);
}
