#pragma once

#include "debugger_core.h"
#include "dbg_err.h"

struct dbg_t *
run_debugger (const char * file_path);

dbg_err_t
get_regs (struct user_regs_struct * regs);
