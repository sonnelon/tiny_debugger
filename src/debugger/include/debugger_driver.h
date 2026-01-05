#pragma once

#include "regs_t.h"

dbg_err_t
run_debugger (const char * file_path);

dbg_err_t
get_regs (struct user_regs_struct * regs);
