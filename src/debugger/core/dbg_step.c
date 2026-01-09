#include <sys/ptrace.h>
#include "dbg_step.h"

dbg_err_t dbg_core_step (struct dbg_t * dbg) 
{
    if (dbg->child_state == CHILD_NOTHING) return DBG_ERR_NO_START;

    dbg->child_state = CHILD_RUNNING;
    
    ptrace(PTRACE_SINGLESTEP, dbg->pid, NULL, NULL);
    return dbg_core_wait(dbg);
}
