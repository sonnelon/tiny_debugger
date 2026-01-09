#pragma once
#include <signal.h> 
#include "dbg_err.h"
#include "debugger_driver.h"

dbg_err_t ui_run (char ** argv, int argc, struct dbg_t * dbg, volatile sig_atomic_t * want_exit);
