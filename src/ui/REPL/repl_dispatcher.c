#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/user.h>

#include "repl_dispatcher.h"
#include "logger.h"
#include "dbg_err.h"
#include "dbg_driver.h"
#include "reg_t.h"
#include "repl_split_command.h"
#include "repl_help_command.h"
#include "repl_regs.h"

static inline bool compare_app_value (const char * app, const char * arg_one, const char * arg_two);
static void distribute_commands (const char * app, const char * arg, const char * file_path, struct dbg_t * dbg);

int repl_run_dispatcher (struct dbg_t * dbg, const char * command, const char * file_path) 
{
    int len = strlen(command);

    int app_size = 10;
    int arg_size = 10;

    char * app = (char *)calloc(app_size, sizeof(char));
    char * arg = (char *)calloc(arg_size, sizeof(char));

    split_command(app, arg, command, len, &app_size, &arg_size);

    distribute_commands(app, arg, file_path, dbg);
    free(arg);
    free(app);

    return 0;
}

static void distribute_commands (const char * app, const char * arg, const char * file_path, struct dbg_t * dbg) 
{
	struct user_regs_struct regs;
	unsigned regs_len = 17;
	struct reg_t * registers = calloc(regs_len, sizeof(struct reg_t));
    if (compare_app_value(app, "h", "help")) 
	{
		help_command();
		return;
	}

    if (compare_app_value(app, "r", "run")) 
	{
        if (dbg_driver_run(dbg, file_path) == DBG_ERR_START)
			log_err("The debugger is already start.");
        return;
    }

    if (compare_app_value(app, "regs", NULL)) 
	{
        if (dbg_driver_get_regs(&regs, dbg) == DBG_ERR_NO_START) 
		{
            log_err("The debugger is not running.");
            return;
        }

		init_regs(&regs, registers, regs_len);
        view_regs(registers, regs_len);
		goto free_regs;
    }

	if (compare_app_value(app, "reg", NULL))
	{
		if (strlen(arg) < 2) goto free_regs;
        if (dbg_driver_get_regs(&regs, dbg) == DBG_ERR_NO_START) 
		{
            log_err("The debugger is not running.");
            return;
        }

		init_regs(&regs, registers, regs_len);
		view_reg(arg, registers, regs_len);
		goto free_regs;
	}

    if (compare_app_value(app, "s", "step")) dbg_driver_step(dbg);
    if (compare_app_value(app, "e", "exit")) dbg_driver_exit(dbg);

free_regs:
	free_regs(registers);
	return;
}

static inline bool compare_app_value (const char * app, const char * arg_one, const char * arg_two)
{
	return (strcmp(app, arg_one) == 0) || ((arg_two == NULL) ? 0 : (strcmp(app, arg_two) == 0));
}
