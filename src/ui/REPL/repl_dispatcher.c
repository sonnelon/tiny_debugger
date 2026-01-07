#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/user.h>

#include "repl_dispatcher.h"
#include "logger.h"
#include "dbg_err.h"
#include "debugger_driver.h"

struct reg_t { char * name; unsigned long value; };

static void
distribute_commands (const char * app, const char * arg, const char * file_path, struct dbg_t * dbg);

static void
help_command ();

static void 
split_command (char * app, char * arg, const char * command, int len, int * app_size, int * arg_size);

static void
realloc_mem (char ** mem, size_t new_sz, int * old_sz);

static inline void
view_regs (const struct user_regs_struct * regs);

int 
repl_run_dispatcher (struct dbg_t * dbg, const char * command, const char * file_path) {
    int len = strlen(command);

    int app_size = 10;
    int arg_size = 10;

    char * app = (char *)calloc(app_size, sizeof(char));
    char * arg = (char *)calloc(arg_size, sizeof(char));

    split_command(app, arg, command, len, &app_size, &arg_size);

    distribute_commands(app, arg, file_path, dbg);
    free(arg);
    free(app);

    return 0;
}

static void
distribute_commands (const char * app, const char * arg, const char * file_path, struct dbg_t * dbg) {
    if (strcmp(app, "h") == 0) { help_command(); return; }
    if (strcmp(app, "r") == 0) {
        dbg_err_t err = dbg_driver_run(dbg, file_path);
        if (err == DBG_ERR_START) log_err("The debugger is already start.");
        return;
    } 

    if (strcmp(app, "regs") == 0) {
        struct user_regs_struct regs;
        if (dbg_driver_get_regs(&regs, dbg) == DBG_ERR_NO_START) {
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
    puts("reg [NAME]   Get the value of register by name.");
    puts("r   [OPTS]   Start a program.");
    puts("b   [ADDR]   Set a breakpoint.");
    puts("e            Exit the program.");
}

static inline void
view_regs (const struct user_regs_struct * regs) {
    struct reg_t registers[] = {
        {"rax", regs->rax},
        {"rbx", regs->rbx},
        {"rcx", regs->rcx},
        {"rdx", regs->rdx},
        {"rsi", regs->rsi},
        {"rdi", regs->rdi},
        {"rbp", regs->rbp},
        {"rsp", regs->rsp},
        {"rip", regs->rip},
        {"r8", regs->r8},
        {"r9", regs->r9},
        {"r10", regs->r10},
        {"r11", regs->r11},
        {"r12", regs->r12},
        {"r13", regs->r13},
        {"r14", regs->r14},
        {"r15", regs->r15}
    };

    const int registers_len = sizeof(registers)/sizeof(registers[0]);

    for (int i = 0; i < registers_len; i++) printf("%s --- 0x%lx\n", registers[i].name, registers[i].value);
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
