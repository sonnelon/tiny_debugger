#include "debugger_driver.h"

struct dbg_t * 
init_dbg () { return create_dbg(); }

dbg_err_t
run_debugger (struct dbg_t * dbg, const char * file_path) {
    if (dbg->child_state != CHILD_NOTHING) return DBG_ERR_START;

    dbg_err_t err = run_dbg(dbg, file_path);
    if (err != DBG_OK) return err;
    
    return DBG_OK;
}

dbg_err_t
get_regs (struct user_regs_struct * regs, struct dbg_t * dbg) {
    if (dbg == NULL || regs == NULL) return DBG_ERR_INVALID_ARG;

    dbg_err_t err = wait_dbg(dbg);
    if (err != DBG_OK) return err;

    err = get_regs(dbg, regs);
    if (err != DBG_OK) return err;

    return DBG_OK;
}
