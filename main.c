#include <signal.h>

#include "ui_driver.h"
#include "debugger_driver.h"
#include "logger.h"

#define CREATE_SIGNAL_HANDLER(func_name, action) \
    void func_name(int sig_num) { \
        (void)sig_num; \
        action; \
    }

int
main (int argc, char * argv[]) {
    struct dbg_t * dbg = dbg_driver_init();

    if (dbg == NULL) {
        log_err("failed init dbg struct.");
        return -1;
    }
    
    CREATE_SIGNAL_HANDLER(sigint_handler, dbg_driver_exit(dbg));
    signal(SIGINT, sigint_handler);

    if (ui_run(argv, argc, dbg) != 0) return -1;
}
