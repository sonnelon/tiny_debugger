#include <sys/ptrace.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugger_core.h"

static inline bool
child_is_stopped (enum dbg_state state);

struct dbg_t *
create_dbg () {
    struct dbg_t * dbg_ptr = (struct dbg_t *)calloc(1, sizeof(struct dbg_t));
    return dbg_ptr;
}

dbg_err_t
run_dbg (struct dbg_t * dbg, const char * file_path) {
    if (dbg == NULL) return DBG_ERR_INVALID_ARG;

    pid_t pid = fork();

    if (pid == -1) return DBG_ERR_FAILED_CREATE_PROCCESS;
    
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        raise(SIGSTOP);
        execve(file_path, NULL, NULL);
        _exit(1);
    }

    dbg->pid = pid;
    dbg->child_state = CHILD_CREATED;

    return DBG_OK;
}

dbg_err_t 
wait_dbg (struct dbg_t * dbg) {
    if (dbg == NULL) return DBG_ERR_INVALID_ARG;
    
    while (1) {
        int status;
        waitpid(dbg->pid, &status, 0);

        if (WIFEXITED(status)) { 
            dbg->child_state = CHILD_EXITED;
            return DBG_ERR_CHILD_EXIT;
        }

        if (WIFSTOPPED(status)) { 
            dbg->child_state = CHILD_STOPPED; 
            break; 
        }
    }

    return DBG_OK;
}

dbg_err_t
get_regs (const struct dbg_t * dbg, struct user_regs_struct * regs) {
    if (dbg == NULL) return DBG_ERR_INVALID_ARG;

    if (child_is_stopped(dbg->child_state)) wait_dbg(dbg);

    ptrace(PTRACE_GETREGS, dbg->pid, NULL, regs);

    return DBG_OK;
}

dbg_err_t 
continue_child (struct dbg_t * dbg) {
    if (dbg == NULL) return DBG_ERR_INVALID_ARG;
    
    if (child_is_stopped(dbg->state)) return DBG_FAIL;
    
    ptrace(PTRACE_CONT, dbg->pid, NULL, NULL);
    dbg->child_state = CHILD_RUNNING;

    return DBG_OK;
}

static inline bool
child_is_stopped (enum dbg_state state) { 
    return state == CHILD_STOPPED;
}
