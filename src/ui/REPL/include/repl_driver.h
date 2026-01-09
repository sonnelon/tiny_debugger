#pragma once
#include <signal.h> 
#include "dbg_err.h"
#include "dbg_driver.h"

dbg_err_t repl_run (const char * file_path, struct dbg_t * dbg, volatile sig_atomic_t * want_exit);
