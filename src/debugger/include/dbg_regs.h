#pragma once
#include "dbg_err.h"
#include "dbg_core.h"
#include "reg_t.h"

dbg_err_t dbg_core_get_regs (const struct dbg_t * dbg, struct user_regs_struct * regs);
unsigned long dbg_core_get_reg_by_name (struct reg_t * regs, const char * name, unsigned regs_len);
