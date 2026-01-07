#pragma once

#include "dbg_err.h"
#include "debugger_driver.h"

dbg_err_t
ui_run (char ** argv, int argc, struct dbg_t * dbg);
