#ifndef _NUCLEUS_H_
#define _NUCLEUS_H_

#include <stddef.h>

// This define is valid if L2 cache is enabled, otherwise 0xC0000000
#define MEM_NONCACHE_OFFSET 0xC0000000 //0x40000000

extern void cpu_data_memory_barrier(void);

#define KERNEL_LOG_SIZE 16

#define CONSOLE_ROWS 16 

void print(const char*);

#endif