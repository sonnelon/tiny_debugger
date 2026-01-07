#include <signal.h>

#include "ui_driver.h"
#include "debugger_driver.h"
#include "logger.h"

volatile sig_atomic_t want_exit = 0;

static inline void
sigint_handler (int signum);

static inline void
register_sigint_action ();

int
main (int argc, char * argv[]) {
    struct dbg_t * dbg = dbg_driver_init();

    if (dbg == NULL) {
        log_err("failed init dbg struct.");
        return -1;
    }
    
    register_sigint_action();

    while (1) {
        if (want_exit) { dbg_driver_exit(dbg); break; }
        if (ui_run(argv, argc, dbg, &want_exit) != DBG_OK) break;
    }

    return 0;
}

static inline void
sigint_handler (int signum) {
    (void)signum;
    want_exit = 1;
}

static inline void
register_sigint_action () {
    struct sigaction sa = {0};
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
}
