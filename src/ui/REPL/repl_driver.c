#include <stdio.h>
#include "repl_driver.h"

static void clean_stdin();

int run_repl(const char * file_path) {
    while (1) {
        printf("(tbg) ");
        char s;
        scanf("%c", &s);
        printf("%c\n", s);
        clean_stdin();
    }

    return 0;
}

void clean_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
