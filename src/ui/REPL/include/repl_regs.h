#pragma once
#include <sys/user.h>
#include "reg_t.h"

void init_regs (struct user_regs_struct * regs, struct reg_t * registers, unsigned regs_len);
void view_regs (struct reg_t * registers, unsigned registers_len);
void free_regs (struct reg_t * registers);
void view_reg (const char * name, const struct reg_t * registers, unsigned regs_len);
