#pragma once

#include <unistd.h>
#include <sys/user.h>
#include "dbg_err.h"

enum child_state {
    CHILD_EXITED,
    CHILD_RUNNING,
    CHILD_CREATED,
    CHILD_STOPPED,
    CHILD_NOTHING,
};

struct dbg_t {
    pid_t pid;
    enum child_state child_state;
};

struct dbg_t * dbg_core_create ();
dbg_err_t dbg_core_run (struct dbg_t * dbg, const char * file_path);
dbg_err_t dbg_core_wait (struct dbg_t * dbg);
