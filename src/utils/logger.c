#include <stdio.h>
#include <stdarg.h>
#include "logger.h"
#include "ANSI_colors.h"

void log_err (const char * msg, ...)
{
    va_list args;
    va_start(args, msg);

    printf("%serror:%s ", RED_COLOR, RESET_COLORS);
    vprintf(msg, args);
    printf("\n");

    va_end(args);
}

void log_warning (const char * msg, ...)
{
    va_list args;
    va_start(args, msg);

    printf("%swarning:%s ", YELLOW_COLOR, RESET_COLORS);
    vprintf(msg, args);
    printf("\n");

    va_end(args);
}

void log_info (const char * msg, ...)
{
    va_list args;
    va_start(args, msg);

    printf("%sinformation:%s ", BLUE_COLOR, RESET_COLORS);
    vprintf(msg, args);
    printf("\n");

    va_end(args);
}

