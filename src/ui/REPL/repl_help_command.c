#include <stdio.h>
#include <stdlib.h>
#include "repl_help_command.h"

void help_command () 
{
	const char * help_msgs[] = {
		"h/help       Display this info.",
		"s/step       Enter the function.",
		"n/next       Proceed to the next step.",
		"regs         Get the value of registers.",
		"reg   [NAME] Get the value of register by name.",
		"r/run [OPTS] Start a program.",
		"b     [ADDR] Set a breakpoint.",
		"e/exit       Exit the program.",
	};

	const int help_msgs_len = sizeof(help_msgs)/sizeof(help_msgs[0]);
	for (int i = 0; i < help_msgs_len; i++) puts(help_msgs[i]);
}
