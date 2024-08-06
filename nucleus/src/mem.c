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
    size_t aligned_size = align_to_4_bytes(size);
    void* heap_end = (void*)((char*)small_heap + SMALL_HEAP_SIZE);

    for (int i = 0; i < SMALL_HEAP_MAXFRAGMENTS; i++) {
        struct mem_sheap_fragment* frag = &small_heap_fragments[i];

        if (!frag->used) {
            void* alloc_start = (i == 0) ? small_heap : 
                (void*)align_to_4_bytes((size_t)(small_heap_fragments[i-1].address + small_heap_fragments[i-1].len));

            if (alloc_start + aligned_size <= heap_end) {
                frag->used = true;
                frag->len = aligned_size;
                frag->address = alloc_start;
                return alloc_start;
            }
        }
    }

    // No suitable fragment found or heap is full
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