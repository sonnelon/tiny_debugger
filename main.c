#include "ui_driver.h"

int
main (int argc, char * argv[]) {
    if (ui_run(argv, argc) != 0) return -1;
}
