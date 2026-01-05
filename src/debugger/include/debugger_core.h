#pragma once

#include <unistd.h>
#include <sys/user.h>
#include "dbg_err.h"

enum child_state {
    CHILD_EXITED,
    CHILD_RUNNING,
    CHILD_CREATED,
    CHILD_STOPPED,
    CHILD_NOTHING
}

struct dbg_t {
    pid_t pid;
    enum child_state child_state;
}

struct dbg_t *
create_dbg ();

dbg_err_t
run_dbg (struct dbg_t * dbg);

dbg_err_t 
wait_dbg (struct dbg_t * dbg);

dbg_err_t 
continue_child (struct dbg_t * dbg);

dbg_err_t
get_regs (const struct dbg_t * dbg, struct user_regs_struct * regs);
