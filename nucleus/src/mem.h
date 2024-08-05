#ifndef _MEM_H_
#define _MEM_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

void mem_init(void);

void* nuc_malloc(size_t size, int flags);
void  nuc_free(void* buf);

// A memory fragment within the small heap
struct mem_sheap_fragment {
    void* address;  // ARM physical address (we're not using the MMU yet)
    short len;      // Length of the memory block or 0 if not allocated
    bool used;      // Is this fragment in use or not?
};

#endif