#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dispatcher.h"
#include "logger.h"
#include "dbg_err.h"

static void
distribute_commands (const char * app, const char * arg, const char * file_path);

static void
help_command ();

static dbg_err_t 
run_dbg (const char * file_path);

static void 
split_command (char * app, char * arg, const char * command, int len, int * app_size, int * arg_size);

static void
realloc_mem (char ** mem, size_t new_sz, int * old_sz);

int 
run_dispatcher (const char * command, const char * file_path) {
    int len = strlen(command);

    int app_size = 10;
    int arg_size = 10;

    char * app = (char *)malloc(app_size * sizeof(char));
    char * arg = (char *)malloc(arg_size * sizeof(char));

    split_command(app, arg, command, len, &app_size, &arg_size);

    distribute_commands(app, arg, file_path);
    free(arg);
}

static void
distribute_commands (const char * app, const char * arg, const char * file_path) {
    if (strcmp(app, "h") == 0) { help_command(); return; }
    if (strcmp(app, "r") == 0) { 
        if (run_dbg(file_path) == DBG_ERR_START) {
            log_info("The debugger is already running.");
            return;
        }
    }

    help_command();
}

static void
help_command () {
    puts("h            Display this info.");
    puts("s            Enter the function.");
    puts("n            Proceed to the next step.");
    puts("regs         Get the value of registers.");
    puts("r [OPTS]     Start a program.");
    puts("b [ADDR]     Set a breakpoint.");
    puts("e            Exit the program.");
}

static dbg_err_t 
run_dbg (const char * file_path) {
    return DBG_OK;
}

static void 
split_command (char * app, char * arg, const char * command, int len, int * app_size, int * arg_size) {
    int app_counter = 0;
    int arg_counter = 0;
    bool app_end = false;

    for (int i = 0; i < len; i++) {
        if (command[i] == '\n') break;

        if (app_counter >= *app_size) realloc_mem(&app, 2*(*app_size), app_size);
        if (arg_counter >= *arg_size) realloc_mem(&arg, 2*(*arg_size), arg_size);

        if (command[i] == ' ' && !app_end) { 
            app_end = true;
            app[app_counter] = '\0';
            continue;
        }

        if (command[i] == ' ' && app_end) continue;

        if (!app_end) {
            app[app_counter++] = command[i];
            continue;
        }
        
        arg[arg_counter++] = command[i];
    }

    arg[arg_counter] = '\0';
}

static void
realloc_mem (char ** mem, size_t new_sz, int * old_sz) {
    char * ptr = (char *)realloc(*mem, new_sz);
    *old_sz = new_sz;
    *mem = ptr;
}
