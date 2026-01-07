#include <stdio.h>
#include "config.h"
#include "ui_cli.h"

void
cli_display_help() {
    printf("Usage: %s [FLAGS].. [FILE]\n", DBG_NAME);
    puts("Options: ");
    puts("      --help    Display this info and exit.");
    puts("      --version Display current version and exit.");
}

void
cli_display_version() { printf("%s current version: %s\n", DBG_NAME, DBG_VERSION); }
