#pragma once

#include "debugger_core.h"
#include "dbg_err.h"

struct dbg_t * 
init_dbg () { return create_dbg(); }

dbg_err_t
run_debugger (struct dbg_t * dbg, const char * file_path);

dbg_err_t
get_regs (struct user_regs_struct * regs, struct dbg_t * dbg);
