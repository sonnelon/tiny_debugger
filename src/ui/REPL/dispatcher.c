#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/user.h>

#include "dispatcher.h"
#include "logger.h"
#include "dbg_err.h"
#include "debugger_driver.h"

struct reg_t { const char * name; unsigned long value; }

static void
distribute_commands (const char * app, const char * arg, const char * file_path, struct dbg_t * dbg);

static void
help_command ();

static dbg_err_t 
run_dbg (const char * file_path);

static void 
split_command (char * app, char * arg, const char * command, int len, int * app_size, int * arg_size);

static void
realloc_mem (char ** mem, size_t new_sz, int * old_sz);

static inline void
view_regs (const struct user_regs_struct * regs);

int 
run_dispatcher (struct dbg_t * dbg, const char * command, const char * file_path) {
    int len = strlen(command);

    int app_size = 10;
    int arg_size = 10;

    char * app = (char *)calloc(app_size, sizeof(char));
    char * arg = (char *)calloc(arg_size, sizeof(char));

    split_command(app, arg, command, len, &app_size, &arg_size);

    distribute_commands(app, arg, file_path, dbg);
    free(arg);
    free(app);
}

static void
distribute_commands (const char * app, const char * arg, const char * file_path, struct dbg_t * dbg) {
    if (strcmp(app, "h") == 0) { help_command(); return; }
    if (strcmp(app, "r") == 0) { 
        if (run_dbg(file_path, dbg) == DBG_ERR_START) {
            log_info("The debugger is already running.");
            return;
        }
    }

    if (strcmp(app, "regs") == 0) {
        struct user_regs_struct regs;
        if (get_regs(&regs, dbg) == DBG_ERR_NO_START) {
            log_err("The debugger is not running.");
            return;
        }

        view_regs(&regs);
    }

    help_command();
}

static void
help_command () {
    puts("h            Display this info.");
    puts("s            Enter the function.");
    puts("n            Proceed to the next step.");
    puts("regs         Get the value of registers.");
    puts("reg [name]   Get the value of register by name.");
    puts("r [OPTS]     Start a program.");
    puts("b [ADDR]     Set a breakpoint.");
    puts("e            Exit the program.");
}

static dbg_err_t 
run_dbg (const char * file_path, struct dbg_t * dbg) {
    return run_dbg(dbg, file_path);
}

static inline void
view_regs (const struct user_regs_struct * regs) {
    int registers_len = 4;
    const reg_t registers[registers_len] = {
        {"sp", regs->sp}, {"pc", regs->pc}, {"ebp", reg->ebp}, {"erp", reg->erp}, {"rip", reg->rip},
    };

    for (int i = 0; i < registers_len; i++) printf("%s --- %d", registers[i]->name, register[i]->value);
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
