#include <stdlib.h>
#include "repl_split_command.h"

static inline void realloc_mem (char ** mem, size_t new_sz, int * old_sz);

void split_command (char * app, char * arg, const char * command, int len, int * app_size, int * arg_size) 
{
    int app_counter = 0;
    int arg_counter = 0;
    bool app_end = false;

    for (int i = 0; i < len; i++) 
	{
        if (command[i] == '\n') break;

        if (app_counter >= *app_size) realloc_mem(&app, 2*(*app_size), app_size);
        if (arg_counter >= *arg_size) realloc_mem(&arg, 2*(*arg_size), arg_size);

        if (command[i] == ' ' && !app_end) 
		{ 
            app_end = true;
            app[app_counter] = '\0';
            continue;
        }

        if (command[i] == ' ' && app_end) continue;

        if (!app_end) 
		{
            app[app_counter++] = command[i];
            continue;
        }
        
        arg[arg_counter++] = command[i];
    }

    arg[arg_counter] = '\0';
}

static inline void realloc_mem (char ** mem, size_t new_sz, int * old_sz) 
{
    char * ptr = (char *)realloc(*mem, new_sz);
    *old_sz = new_sz;
    *mem = ptr;
}
