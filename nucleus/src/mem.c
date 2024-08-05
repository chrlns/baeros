#include "mem.h"
#include "nucleus.h"

#define SMALL_HEAP_SIZE 4096
#define SMALL_HEAP_MAXFRAGMENTS 64
extern void* small_heap;

struct mem_sheap_fragment small_heap_fragments[SMALL_HEAP_MAXFRAGMENTS];

void zeroes(void* address, size_t len) {
    while(len-- > 0) {
        *((char*)address) = 0;
        address++;
    }
}

void mem_init() {
    zeroes(small_heap, SMALL_HEAP_SIZE);
    for (size_t i = 0; i < SMALL_HEAP_MAXFRAGMENTS; i++) {
        small_heap_fragments[i].address = NULL;
        small_heap_fragments[i].len = 0;
        small_heap_fragments[i].used = false;
    }
    
}

static size_t align_to_4_bytes(size_t size) {
    return (size + 3) & ~3;
}

void* nuc_malloc(size_t size, int flags) {
    void* next_start = small_heap;

    for (int i = 0; i < SMALL_HEAP_MAXFRAGMENTS; i++) {
        struct mem_sheap_fragment* frag = &small_heap_fragments[i];

        if (frag->used) {
            next_start = (void*)align_to_4_bytes((size_t)(frag->address + frag->len));
        } else {
            if (frag->address != NULL && frag->len >= size) {
                // Fragment has been used before and fits the size
                frag->used = true;
                return frag->address;
            } else {
                frag->used = true;
                frag->len = align_to_4_bytes(size);
                frag->address = next_start;
                return next_start;
            }
        }
    }
    return NULL;
}

void nuc_free(void* buf) {
    for (int i = 0; i < SMALL_HEAP_MAXFRAGMENTS; i++) {
        if (small_heap_fragments[i].address == buf) {
            zeroes(buf, small_heap_fragments[i].len);
            small_heap_fragments[i].address = NULL;
            return;
        }
    }
    // Double free
    print("Warning: double free\n");
}