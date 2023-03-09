#pragma once

#define MODULE_ADDR		0xffffffff00000000
#define KERNEL_ADDR		0xffffffff80000000

/* Those are sv48 values */
#define PAGE_OFFSET		0xffffaf8000000000
#define TASK_SIZE		(1UL << 47)

#define PAGE_SHIFT		12
#define PTE_FILE_MAX_BITS	60

#define PTRACE_GETREGS		0
#define PTRACE_GETFPREGS	0
#define PTRACE_SETREGS		0
#define PTRACE_SETFPREGS	0

#define SYSCALLS syscalls_riscv64
