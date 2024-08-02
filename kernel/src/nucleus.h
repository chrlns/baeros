//#define NULL 0
#include <stddef.h>

// This define is valid if L2 cache is enabled, otherwise 0xC0000000
#define MEM_NONCACHE_OFFSET 0xC0000000 //0x40000000

extern void cpu_data_memory_barrier(void);
