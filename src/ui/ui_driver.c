#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "ui_driver.h"
#include "repl_driver.h"
#include "args_t.h"
#include "cli.h"
#include "logger.h"

#define HELP_FLAG "--help"
#define VERSION_FLAG "--version"

static struct args_t * 
parse_args (char ** argv, int argc);

static inline bool
is_correct_file (const char * file_path);

int
run_ui (char ** argv, int argc) {
    if (argc == 1) { 
        log_err("the path to the file is missing.");
        return -1; 
    }
    
    struct args_t * args = parse_args(argv, argc);
    if (args == NULL) { 
        log_err("failed to allocate memmory.");
        return -1; 
    }

    if (args->help) { display_help(); return 0; }
    if (args->version) { display_version(); return 0; }
    
    if (strlen(args->file_path) != 0) { 
        if (!is_correct_file(args->file_path)) return -1;
        if (run_repl(args->file_path) != 0) return -1;
    }

    free(args);
    return 0;
}

static struct args_t *
parse_args (char ** argv, int argc) {
    struct args_t * args = (struct args_t *)calloc(1, sizeof(struct args_t));
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], HELP_FLAG) == 0) { args->help = 1; break; }
        if (strcmp(argv[i], VERSION_FLAG) == 0) { args->version = 1; break; }
    }
    
    if (!args->help && !args->version) {
        size_t len = strlen(argv[argc-1]);
        args->file_path = malloc(len + 1);
        if (args->file_path == NULL) {
            log_err("failed to allocate memory.");
            free(args);
            return NULL;
        }

        strcpy(args->file_path, argv[argc-1]);
    }

    return args;
}

static inline bool
is_correct_file (const char * file_path) {
    if (access(file_path, X_OK) != 0) {
        log_err("file is not executable.");
        return false;
    }

    return true;
}
