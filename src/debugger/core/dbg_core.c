#include <stdio.h>
#include <sys/ptrace.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>

#include "dbg_core.h"
#include "logger.h"

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
            log_info("The process received a signal: %d", sig);
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
