#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repl_regs.h"

static inline void display_register (const char * name, unsigned long value);

void view_regs (struct reg_t * registers, unsigned registers_len) 
{
    for (int i = 0; i < registers_len; i++) display_register(registers[i].name, registers[i].value);
}

void init_regs (struct user_regs_struct * regs, struct reg_t * registers, unsigned regs_len)
{
    if (regs_len < 17) return;

    const char * names[] = {
        "rax","rbx","rcx","rdx","rsi","rdi","rbp","rsp","rip",
        "r8","r9","r10","r11","r12","r13","r14","r15"
    };

    unsigned long values[] = {
        regs->rax, regs->rbx, regs->rcx, regs->rdx,
        regs->rsi, regs->rdi, regs->rbp, regs->rsp, regs->rip,
        regs->r8,  regs->r9,  regs->r10, regs->r11,
        regs->r12, regs->r13, regs->r14, regs->r15
    };

    for (int i = 0; i < regs_len; i++) {
        registers[i].name  = names[i];
        registers[i].value = values[i];
    }
}

void view_reg (const char * name, const struct reg_t * registers, unsigned regs_len)
{
	for (int i = 0; i < regs_len; i++) 
	{
		if (strcmp(name, registers[i].name) == 0) display_register(registers[i].name, registers[i].value);
	}
}

void free_regs (struct reg_t * registers)
{
	free(registers);
}

static inline void display_register (const char * name, unsigned long value)
{
	printf("%s --- 0x%lx\n", name, value);
}
