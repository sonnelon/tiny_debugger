#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dispatcher.h"

static void
distribute_commands (char app, const char * arg);

static void
help_command ();

static void
run_debugger (const char * file_path);

static void 
split_command (char * app, char * arg, const char * command, int len);

static void
realloc_mem (char ** mem, size_t new_sz, int * old_sz);

int 
run_dispatcher (const char * command) {
    char app = command[0];
    int len = strlen(command);
    char * arg = (char *)malloc((len-2) * sizeof(char));
    for (int i = 2; i < len; i++) arg[i-2] = command[i];

    distribute_commands(app, arg);
    free(arg);
}

static void
distribute_commands (char app, const char * arg) {
    switch (app) {
        case 'h': help_command(); break;
        case 'e': return;
        default: help_command(); break;
    }
}

static void
help_command () {
    puts("h            Display this info.");
    puts("s            Enter the function.");
    puts("n            Proceed to the next step.");
    puts("r [OPTS]     Start a program.");
    puts("b [ADDR]     Set a breakpoint.");
    puts("e            Exit the program.");
}

static void
run_debugger (const char * file_path) {
    struct dbg_t * dbg = run_debugger(file_path);
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
