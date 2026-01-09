#include <stdlib.h>
#include <stdio.h>
#include <sys/ptrace.h>

#include "dbg_exit.h"
#include "logger.h"

void dbg_core_exit (struct dbg_t * dbg) 
{
    printf("\n");
    log_info("Gracefull shutdown started");
	ptrace(PTRACE_CONT, dbg->pid, 0, 0);
	dbg_core_wait(dbg);
    ptrace(PTRACE_DETACH, dbg->pid, NULL, NULL);
    free(dbg);
    log_info("Successfuly exit.");
    _exit(0);
}
