#pragma once

#include "dbg_err.h"
#include "debugger_driver.h"

dbg_err_t
repl_run (const char * file_path, struct dbg_t * dbg);
