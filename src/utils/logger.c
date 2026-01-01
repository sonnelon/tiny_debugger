#include <stdio.h>
#include "logger.h"
#include "ANSI_colors.h"

void
log_err (const char * msg) { 
    printf("%serror:%s %s\n", RED_COLOR, RESET_COLORS, msg); 
}

void 
log_warning (const char * msg) { 
    printf("%swarning:%s %s\n", YELLOW_COLOR, RESET_COLORS, msg); 
}

void
log_info (const char * msg) { 
    printf("%sinformation:%s %s\n", BLUE_COLOR, RESET_COLORS, msg); 
}
