#pragma once

#include "debugger_core.h"
#include "dbg_err.h"

struct dbg_t * dbg_driver_init ();

dbg_err_t dbg_driver_run (struct dbg_t * dbg, const char * file_path);

dbg_err_t dbg_driver_get_regs (struct user_regs_struct * regs, struct dbg_t * dbg);

dbg_err_t dbg_driver_step (struct dbg_t * dbg);

void dbg_driver_exit (struct dbg_t * dbg);
