#include <stdio.h>
#include <sys/ptrace.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>

#include "debugger_core.h"
#include "logger.h"

static inline bool child_is_stopped (enum child_state state);

struct dbg_t * dbg_core_create ()
{
    struct dbg_t * dbg_ptr = (struct dbg_t *)calloc(1, sizeof(struct dbg_t));
    dbg_ptr->child_state = CHILD_NOTHING;
    return dbg_ptr;
}

dbg_err_t dbg_core_run (struct dbg_t * dbg, const char * file_path) 
{
    if (dbg->child_state == CHILD_CREATED) return DBG_ERR_START;

    pid_t pid = fork();

    if (pid == -1) return DBG_ERR_FAILED_CREATE_PROCCESS;
    
    if (pid == 0) 
	{
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        raise(SIGSTOP);
        signal(SIGINT, SIG_IGN);
        execve(file_path, NULL, NULL);
        _exit(1);
    }

    dbg->pid = pid;
    dbg->child_state = CHILD_CREATED;

	log_info("PID of process: %d", pid);

    return DBG_OK;
}

dbg_err_t dbg_core_wait (struct dbg_t * dbg) 
{
    if (dbg->child_state == CHILD_NOTHING) return DBG_ERR_NO_START;
    
    while (1) 
	{
        int status;
        waitpid(dbg->pid, &status, 0);

        if (WIFSIGNALED(status)) 
		{
            int sig = WTERMSIG(status);
            printf("The process received a signal: %d\n", sig);
            ptrace(PTRACE_CONT, dbg->pid, 0, 0);
		}

        if (WIFEXITED(status)) 
		{ 
            dbg->child_state = CHILD_EXITED;
            return DBG_ERR_CHILD_EXIT;
        }

        if (WIFSTOPPED(status)) 
		{ 
            dbg->child_state = CHILD_STOPPED; 
            break; 
        }
    }

    return DBG_OK;
}

dbg_err_t dbg_core_step (struct dbg_t * dbg) 
{
    if (dbg->child_state == CHILD_NOTHING) return DBG_ERR_NO_START;

    dbg->child_state = CHILD_RUNNING;
    
    ptrace(PTRACE_SINGLESTEP, dbg->pid, NULL, NULL);
    return dbg_core_wait(dbg);
}

dbg_err_t dbg_core_get_regs (const struct dbg_t * dbg, struct user_regs_struct * regs) 
{
    if (dbg->child_state == CHILD_NOTHING) return DBG_ERR_NO_START;

    ptrace(PTRACE_GETREGS, dbg->pid, NULL, regs);
    return DBG_OK;
}

dbg_err_t dbg_core_continue_child (struct dbg_t * dbg) 
{
    if (dbg->child_state == CHILD_NOTHING) return DBG_ERR_NO_START;

    if (child_is_stopped(dbg->child_state)) return DBG_FAIL;
    
    ptrace(PTRACE_CONT, dbg->pid, NULL, NULL);
    dbg->child_state = CHILD_RUNNING;
    dbg_core_wait(dbg);

    return DBG_OK;
}

void dbg_core_exit (struct dbg_t * dbg) 
{
    printf("\n");
    log_info("Gracefull shutdown started");
    ptrace(PTRACE_DETACH, dbg->pid, NULL, NULL);
    free(dbg);
    log_info("Successfuly exit.");
    _exit(0);
}

static inline bool child_is_stopped (enum child_state state) 
{ 
    return state == CHILD_STOPPED;
}
