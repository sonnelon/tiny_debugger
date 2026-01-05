#include "debugger_driver.h"

struct dbg_t *
run_debugger (const char * file_path) {
    struct dbg_t * dbg = create_dbg();
    if (dbg == NULL) return NULL;

    dbg_err_t err = run_dbg(dbg);
    if (err != DBG_OK) {
        free(dbg);
        return NULL;
    }

    return dbg;
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
