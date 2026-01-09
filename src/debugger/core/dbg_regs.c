#include <sys/ptrace.h>
#include <stdio.h>
#include "dbg_regs.h"

dbg_err_t dbg_core_get_regs (const struct dbg_t * dbg, struct user_regs_struct * regs) 
{
    if (dbg->child_state == CHILD_NOTHING) return DBG_ERR_NO_START;

    ptrace(PTRACE_GETREGS, dbg->pid, NULL, regs);
    return DBG_OK;
}
