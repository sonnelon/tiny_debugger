#pragma once

#include "regs_t.h"

int
run_debugger (const char * file_path);

int 
next_step ();

int 
set_breakpoint ();

struct regs_t
get_regs ();

int 
enter_to_func ();

int
shutdown ();
