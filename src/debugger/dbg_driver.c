#include "dbg_exit.h"
#include "dbg_core.h"
#include "dbg_step.h"
#include "dbg_regs.h"
#include "dbg_driver.h"

struct dbg_t * dbg_driver_init () 
{ 
	return dbg_core_create(); 
}

dbg_err_t dbg_driver_run (struct dbg_t * dbg, const char * file_path) 
{
    if (dbg->child_state != CHILD_NOTHING) return DBG_ERR_START;
    return dbg_core_run(dbg, file_path);
}

dbg_err_t dbg_driver_get_regs (struct user_regs_struct * regs, struct dbg_t * dbg) 
{
    return regs && dbg ? dbg_core_get_regs(dbg, regs) : DBG_ERR_INVALID_ARG;
}

unsigned long dbg_driver_get_reg (struct reg_t * regs, const char * name, unsigned regs_len)
{
	return dbg_core_get_reg_by_name(regs, name, regs_len);
}

dbg_err_t dbg_driver_step (struct dbg_t * dbg) 
{
    return dbg ? dbg_core_step(dbg) : DBG_ERR_INVALID_ARG;
}

void dbg_driver_exit (struct dbg_t * dbg) 
{
	dbg_core_exit(dbg); 
}
