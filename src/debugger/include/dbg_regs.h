#pragma once
#include "dbg_err.h"
#include "dbg_core.h"

dbg_err_t dbg_core_get_regs (const struct dbg_t * dbg, struct user_regs_struct * regs);
