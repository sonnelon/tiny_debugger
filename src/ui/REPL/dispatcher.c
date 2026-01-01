#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dispatcher.h"

static void
distribute_commands (char app, const char * arg);

static void
help_command ();

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
