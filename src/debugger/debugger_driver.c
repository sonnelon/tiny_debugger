#include "debugger_driver.h"

struct dbg_t * 
dbg_driver_init () { return dbg_core_create(); }

dbg_err_t
dbg_driver_run (struct dbg_t * dbg, const char * file_path) {
    if (dbg->child_state != CHILD_NOTHING) return DBG_ERR_START;

    dbg_err_t err = dbg_core_run(dbg, file_path);
    if (err != DBG_OK) return err;
    
    return DBG_OK;
}

dbg_err_t
dbg_driver_get_regs (struct user_regs_struct * regs, struct dbg_t * dbg) {
    if (dbg == NULL || regs == NULL) return DBG_ERR_INVALID_ARG;

    dbg_err_t err = dbg_core_wait(dbg);
    if (err != DBG_OK) return err;

    err = dbg_core_get_regs(dbg, regs);
    if (err != DBG_OK) return err;

    return DBG_OK;
}

void
dbg_driver_exit (struct dbg_t * dbg) { dbg_core_exit(dbg); }
