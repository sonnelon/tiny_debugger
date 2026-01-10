#include <sys/ptrace.h>
#include <stdio.h>
#include <string.h>
#include "dbg_regs.h"

static inline bool is_reg (const char * name, const char * reg_name);

dbg_err_t dbg_core_get_regs (const struct dbg_t * dbg, struct user_regs_struct * regs) 
{
    if (dbg->child_state == CHILD_NOTHING) return DBG_ERR_NO_START;

    ptrace(PTRACE_GETREGS, dbg->pid, NULL, regs);
    return DBG_OK;
}

unsigned long dbg_core_get_reg_by_name (struct reg_t * regs, const char * name, unsigned regs_len)
{
	if (!regs) return -1;
	for (int i = 0; i < regs_len; i++)
		if (is_reg(name, regs->name)) return regs->value;
	return -1;
}

static inline bool is_reg (const char * name, const char * reg_name)
{
	return strcmp(name, reg_name) == 0;
}
