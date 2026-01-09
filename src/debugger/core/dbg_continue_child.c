#include <sys/ptrace.h>

#include "dbg_continue_child.h"

static inline bool child_is_stopped (enum child_state state);

dbg_err_t dbg_core_continue_child (struct dbg_t * dbg) 
{
    if (dbg->child_state == CHILD_NOTHING) return DBG_ERR_NO_START;

    if (child_is_stopped(dbg->child_state)) return DBG_FAIL;
    
    ptrace(PTRACE_CONT, dbg->pid, NULL, NULL);
    dbg->child_state = CHILD_RUNNING;
    dbg_core_wait(dbg);

    return DBG_OK;
}

static inline bool child_is_stopped (enum child_state state) 
{ 
    return state == CHILD_STOPPED;
}
